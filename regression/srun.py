#!/usr/bin/env python
#-------------------------------------------------------------------------------
# Simple python script to run tests via srun allocation (salloc) on redsky.
#
# Authors:       K. Noel Belcourt
# Created:       2013/09/07
# Last modified: 2013/09/07
#-------------------------------------------------------------------------------

import os
import select
import string
import time
from subprocess import Popen, PIPE

#-------------------------------------------------------------------------------

class minimal_test:
  def __init__(self, fullpath, runtime, nprocs):
    self.fullpath = fullpath
    self.expected_runtime = runtime
    self.nprocs = nprocs
    self.p = ''
    self.stdout = ''
    self.stderr = ''
    self.job_step = 0
    self.nnodes = 0
    self.starttime = 0
    self.runtime = 0
    self.status_str = ''
    self.starting_node = 0

class srun_testing:
  description = 'Class for use with salloc on Redsky'
  listOfTests = []
  free_list = [] # number of free cores per node, list length is number of nodes
  slurm_cores_per_node = 0
  def __init__(self):
    f = 0
    # open and read file containing tests to run, and command line args
    f = open('srun.dat', 'r')
    # read number of tests
    ntests = int(f.readline())
    # test data: fullpath, expected_runtime, nprocs
    for i in xrange(ntests):
      line = f.readline()
      words = line.split(' ')
      fullpath = words[0]
      expected_runtime = words[1]
      nprocs = int(words[2])
      self.listOfTests.append(minimal_test(fullpath,expected_runtime,nprocs))
    # we're done
    f.close()
    self.run_tests()

  def __del__(self):
    # open and write file containing test results back to runtests.py
    f = open('srun_results.dat', 'w')
    for test in self.listOfTests:
      f.write('%s\n'%test.fullpath)
    f.close()

  # return starting node, and number of free nodes of largest free block
  def get_largest_block(self):
    starting_node = 0
    number_consecutive = 0
    for a in self.free_list:
      if a == self.slurm_cores_per_node:
        # this node is free
          starting_node = a
          number_consecutive = b
      # get index of largest block
      idx = self.free_nodes.index(starting_node)
      del self.free_nodes[idx]
      del self.free_node_sizes[idx]
    print 'largest free block of nodes starts at node %d length %d\n'%(starting_node,number_consecutive)
    return (starting_node,number_consecutive)

  def compress_free_list(self, fn, fns, n):
    # only used n cores of fns * 8 available cores
    nused = int((n + 8) / 8)
    print 'fns = %d\n'%fns
    print 'nused = %d\n'%nused
    if nused < fns:
      self.free_nodes.append(fn+1)
      self.free_node_sizes.append(fns-nused)
    if len(self.free_nodes) <= 1: return
    # compress the list
    a = self.free_nodes.__iter__()
    b = self.free_node_sizes.__iter__()
    a.next()
    b.next()
    for n,m in zip(a,b):
      print 'a = %d b = %d n = %d\n'%(a,b,n)
      if n == a + b:
        print 'compress this range\n'

  def get_test(self):
    if not self.listOfTests: return
    (fn,fns) = self.get_largest_block()
    # n is number of available cores
    n = fns * 8
    for a in self.listOfTests:
      if a.nprocs <= n:
        del self.listOfTests[self.listOfTests.index(a)]
        # insert back into free list if didn't use entire node set
        self.compress_free_list(fn, fns, a.nprocs)
        return a

  def run_tests(self):
    # sacct -n -j 14640793.1
    # sacct -j 14640781

    passed = 0
    failed = 0
    skipped= 0

    # slurm specific data
    slurm_jobid = os.getenv('SLURM_JOB_ID')
    slurm_num_nodes = int(os.getenv('SLURM_JOB_NUM_NODES'))
    self.slurm_cores_per_node = 0
    s = os.getenv('SLURM_JOB_CPUS_PER_NODE')
    if 1 < slurm_num_nodes:
      # slurm sets as 8(xN) where N is slurm_num_nodes
      word = s.rsplit('(')
      self.slurm_cores_per_node = int(word[0])
    else:
      self.slurm_cores_per_node = int(s)
    total_cores = slurm_num_nodes * self.slurm_cores_per_node

    # populate free list
    for i in xrange(slurm_num_nodes):
      self.free_list.append(self.slurm_cores_per_node)

    # track number of cores and nodes in use and free
    n_avail_cores = total_cores
    n_running_cores = 0
    n_avail = slurm_num_nodes
    n_running = 0
    nnodes = 0
    # setup for loop over tests
    done = False
    head = os.getcwd()
    stepid = 0
    running_tests = []
    self.free_nodes.append(0)
    self.free_node_sizes.append(n_avail)
    while not done:
      # get list of available nodes, and number consecutive
      while self.listOfTests and 0 < n_avail:
        test = self.get_test()
        if test:
          nnodes = test.nprocs / self.slurm_cores_per_node
          if 0 != test.nprocs % self.slurm_cores_per_node: nnodes += 1
          cmd = ['srun'] + ['--time=' + test.expected_runtime] + ['--account=FY139321'] + [ '--nodes=' + str(nnodes) ] + ['--relative=' + str(n_running)] + [test.fullpath]
          print 'Executing the command %s' % (cmd)
          n_avail_cores -= test.nprocs
          n_running_cores += test.nprocs
          n_avail -= nnodes
          n_running += nnodes
          test.starting_node = n_running
          test.nnodes = nnodes
          test.job_step = stepid
          test.starttime = time.time()
          stepid += 1
          test.p = Popen(cmd, stdout=PIPE, stderr=PIPE, cwd=head)
          running_tests.append(test)
        else:
          break;
      # wait for any test to complete
      test_terminated = False
      while not test_terminated:
        for test in running_tests:
          cmd = ['sacct'] + ['-n'] + ['-j'] + ['%s.%d'%(slurm_jobid,test.job_step)]
          p = Popen(cmd, stdout=PIPE, stderr=PIPE, cwd=head)
          stdout, stderr = p.communicate()
          status = p.wait()
          is_running = stdout.find('RUNNING')
          if is_running == -1:
            if 0 < stdout.find('FAILED'):
              test.status_str = 'failed'
            elif 0 < stdout.find('COMPLETED'):
              test.status_str = 'passed'
            # set completion status
            if test.status_str:
              test.runtime = time.time() - test.starttime
              n_avail_cores += test.nprocs
              n_running_cores -= test.nprocs
              n_avail += nnodes
              n_running -= nnodes
              test_terminated = True
              self.free_nodes.append(test.starting_node)
              self.free_node_sizes.append(test.nnodes)
              del running_tests[running_tests.index(test)]
              print 'test %s in %s (s)\n'%(test.status_str,test.runtime)
        # just queried job status, wait before doing it again
        time.sleep(5)
      # check if we're finished
      if not self.listOfTests and 0 == n_running: done = True


# create instance of class, and launch jobs
srt = srun_testing()
