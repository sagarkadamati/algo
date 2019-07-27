. "$PSScriptRoot\Audio.ps1"
. "$PSScriptRoot\Video.ps1"

Export-ModuleMember -Function ConcatVideos, AutoCropVideos, AnalizeVideos, GenVideos
Export-ModuleMember -Function Get-SriChalapathiRaoAudio, Update-ID3Files