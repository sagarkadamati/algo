. ([IO.Path]::Combine($PSScriptRoot, "Key Bindings", "Key Bindings.ps1"))
. ([IO.Path]::Combine($PSScriptRoot, "Settings", "Settings.ps1"))
. ([IO.Path]::Combine($PSScriptRoot, "Theme", "Theme.ps1"))

function Update-VSCode {
	Get-VSKeys > ([IO.Path]::Combine($ToolsLocation, "Env", "vssettings", "keybindings.json"))
	Get-VSSettings > ([IO.Path]::Combine($ToolsLocation, "Env", "vssettings", "settings.json"))
	# Get-VSTheme
}

Export-ModuleMember -Function Update-VSCode