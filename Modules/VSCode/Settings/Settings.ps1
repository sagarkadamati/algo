function Get-VSSettings {
	$jsondata  = Get-json $(Join-Path $PSScriptRoot "General.json")

	$jsondata.'git.path' = $(Join-Path $ToolsLocation "Git" | Join-Path -Child "bin" | Join-Path -Child "git.exe")
	$jsondata.'python.pythonPath' = $(Join-Path $ToolsLocation "Python" | Join-Path -Child "python.exe")
	$jsondata.'markdown.styles' = $(Join-Path $ToolsLocation "Env" | Join-Path -Child "vssettings" | Join-Path -Child "css" | Join-Path -Child "markdown.css")

	$jsondata | ConvertTo-Json | Out-File -Encoding UTF8 ([IO.Path]::Combine($ToolsLocation, "Env", "vssettings", "settings.json"))
}