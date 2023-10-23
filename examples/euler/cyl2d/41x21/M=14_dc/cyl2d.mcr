#!MC 1000

# Auxilary variable movie maker

$!VarSet |MFBD| = '/Users/sscoll/Desktop/2dcyl/M=14/'
$!VarSet |data| = 'new.'
$!VarSet |suffix| = '.dat'
$!VarSet |start| = 0
$!VarSet |end|   = 5000 
$!VarSet |inc|   = 100
$!VarSet |NumFiles| = ( ( |end| - |start| ) / |inc| + 1 ) - 1

$!ExportSetup
  ExportFormat = flash
  FlashImageType = Lossless
  ImageWidth = 600
  ExportFName = "|MFBD|movie.swf"
  UseSuperSampleAntiAliasing = Yes 
  SuperSampleFactor = 3
  Quality = 100

$!DoubleBuffer On

$!Loop |NumFiles|
  $!DrawGraphics No
  $!VarSet |step| = ( |start| + ( |loop| - 1 ) * |inc| )
  $!ReadDataSet '"|MFBD||data||step%.1d||suffix|"' ResetStyle = False
    ResetStyle = False
    ReadDataOption = Replace
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

