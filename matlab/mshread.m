function grid = mshread(casename)
% MSHREAD Read DGM .msh file
%
%   GRID = MSHREAD(CASENAME) returns a structure containing
%   the number of space dimensions, the number of elements,
%   and the coordinates for each element.  CASENAME is a the
%   DGM string prefix, assuming that the file CASENAME.msh is
%   accessible.
%
% See also MSHPLOT, TECREAD

% Set the msh file name
casename = strrep(casename, '.msh', '');
fname = [casename '.msh'];

% Open file
if (exist(fname, 'file') == 0), error(['File, ' fname ' does not exist']); end;
fid=fopen(fname);

% Read **MESH DATA** line
A=fgets(fid);

% Read in num of elements and space dimensions
grid.nelem  = fscanf(fid, '%d', 1);
grid.dim    = fscanf(fid, '%d', 1);
A=fgets(fid);

% Read element vertices
grid.element(grid.nelem) = struct('type',[],'coordinates',[]);
for e=1:grid.nelem
  % Read element header line
  A = fgets(fid);
  
  % Get element type
  [estr ielem etype] = strread(A, '%s%d%s');
  grid.element(e).type = lower(etype{1});
  
  % Find out number of element vertices
  switch grid.element(e).type
   case{'line'}
    nvert = 2;
   case{'quad'}
    nvert = 4;
  end
  
  % Read vertices for this element
  A = fscanf(fid, '%f', [nvert grid.dim]);
  grid.element(e).coordinates = A;
  A = fgets(fid);
end

% Close msh file
fclose(fid);
