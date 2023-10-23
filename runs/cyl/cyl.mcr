#!MC 800

# Primitive variable movie maker

$!VarSet |MFBD| = '/home/collis/cyl/'
$!VarSet |data| = 'cyl.'
$!VarSet |start| = 200 
$!VarSet |end|   = 60000 
$!VarSet |inc|   = 200 
$!VarSet |NumFiles| = ( ( |end| - |start| ) / |inc| + 1 ) - 1

$!ExportSetup
  ExportFormat = avi 
  ExportFName = "|MFBD|movie.avi"

$!DoubleBuffer On

$!Loop |NumFiles|
  $!DrawGraphics No
  $!VarSet |step| = ( |start| + ( |loop| - 1 ) * |inc| )
  $!If |step| < 10
    $!ReadDataSet '"|MFBD||data||step%.1d|.plt"' ResetStyle = False
  $!Endif
  $!If |step| > 10 
    $!ReadDataSet '"|MFBD||data||step%.2d|.plt"' ResetStyle = False
  $!EndIf
  $!DrawGraphics Yes
  $!RedrawAll
  $!DoubleBuffer Swap
  $!If |loop| == 1
    $!Export
      Append = No
  $!EndIf
  $!If |loop| > 1
    $!Export
      Append = Yes
  $!EndIf
$!EndLoop

$!DoubleBuffer off
