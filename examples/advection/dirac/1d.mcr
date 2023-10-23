#!MC 800

# Auxilary variable movie maker

$!VarSet |MFBD| = '|$DGM_HOME|/examples/advection/dirac/'
$!VarSet |data| = '1d.'
$!VarSet |suffix| = '.dat'
$!VarSet |start| = 0 
$!VarSet |end|   = 1000 
$!VarSet |inc|   = 50 
$!VarSet |NumFiles| = ( ( |end| - |start| ) / |inc| + 1 ) - 1

$!ExportSetup
  ExportFormat = flash
  UseSuperSampleAntiAliasing = True 
  SuperSampleFactor = 3
  FlashImageType = Lossless
  Quality = 100
  ImageWidth = 600
  ExportFName = "|MFBD|movie.swf"

$!DoubleBuffer On

$!Loop |NumFiles|
  $!DrawGraphics No
  $!VarSet |step| = ( |start| + ( |loop| - 1 ) * |inc| )
  $!ReadDataSet '"|MFBD||data||step%.1d||suffix|"' ResetStyle = False
  $!DrawGraphics Yes
  $!RedrawAll
  $!DoubleBuffer Swap
  $!If |loop|==1
    $!ExportStart
  $!Else
    $!ExportNextFrame
  $!EndIf
$!EndLoop

$!DoubleBuffer off

$!ExportFinish
