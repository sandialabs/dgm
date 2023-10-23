#!MC 1000

# Tecplot movie maker

$!VarSet |MFBD| = '/Users/sscoll/derived_code/tbird2/'
$!VarSet |data| = 'tbird2.'
$!VarSet |suffix| = '.dat'
$!VarSet |start| = 100
$!VarSet |end|   = 4000 
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
  ExportFName = "|MFBD|movie.swf"

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
