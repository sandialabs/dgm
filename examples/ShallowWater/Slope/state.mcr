#!MC 1000

# Tecplot movie maker

$!VarSet |MFBD| = ''
$!VarSet |data| = '2D_bore.'
$!VarSet |suffix| = '_1.dat'
$!VarSet |start| = 0 
$!VarSet |end|   = 1000 
$!VarSet |inc|   = 100
$!VarSet |NumFiles| = ( ( |end| - |start| ) / |inc| + 1 ) - 1

$!ExportSetup
  ExportRegion = AllFrames
  ExportFormat = flash
  UseSuperSampleAntiAliasing = Yes 
  SuperSampleFactor = 3
  FlashImageType = Lossless
  Quality = 100
  ImageWidth = 800 
  ExportFName = "|MFBD|state.swf"

$!DoubleBuffer On

$!Loop |NumFiles|
  $!DrawGraphics No
  $!VarSet |step| = ( |start| + ( |loop| - 1 ) * |inc| )
  $!ReadDataSet '"|MFBD||data||step%.1d||suffix|"' 
    ResetStyle = False
    ReadDataOption = Replace
  $!DrawGraphics Yes
  $!RedrawAll
  $!DoubleBuffer Swap
  $!If |loop|==1
    $!ExportStart
      ExportRegion = AllFrames
  $!Else
    $!ExportNextFrame
  $!EndIf
$!EndLoop

$!DoubleBuffer off

$!ExportFinish
