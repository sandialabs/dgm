#!MC 800

# Primitive variable movie maker

$!VarSet |MFBD| = '/home/collis/dgm/runs/'
$!VarSet |data| = 'bump.'
$!VarSet |start| = 1
$!VarSet |end|   = 40 
$!VarSet |inc|   = 1
$!VarSet |NumFiles| = ( ( |end| - |start| ) / |inc| + 1 ) - 1

$!ExportSetup
  ExportFormat = RasterMetafile 
  ExportFName = "|MFBD|movie.rm"

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
