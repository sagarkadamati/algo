. ([IO.Path]::Combine($PSScriptRoot, "Key Bindings", "Key Bindings.ps1"))
. ([IO.Path]::Combine($PSScriptRoot, "Settings", "Settings.ps1"))
. ([IO.Path]::Combine($PSScriptRoot, "Theme", "Theme.ps1"))

function Get-Json {
	param(
		[String]$File
	)
	process {
		Get-Content $File | ConvertFrom-Json
	}
}

function isVSCodeNotPatched ($File) {
	$isPatched = Get-Content $VSCodeIndexHTML | Select-String -SimpleMatch $CustomCCSLink
	return $(($isPatched).Line -like "")
}

function Get-VSCodePathed {
	$VSCodeIndexHTML = [IO.Path]::Combine($ToolsLocation, "VSCode", "resources", "app", "out", "vs", "workbench", "electron-browser", "bootstrap", "index.html")
	$VSCodeIndexHTML = [IO.Path]::Combine($ToolsLocation, "VSCode", "resources", "app", "out", "vs", "code", "electron-browser", "workbench", "workbench.html")
	$VSCodeMainJS    = [IO.Path]::Combine($ToolsLocation, "VSCode", "resources", "app", "out", "vs", "workbench", "workbench.main.js")
	$CustomCCS       = [IO.Path]::Combine($ToolsLocation, "Env", "vssettings", "css", "noEditorActionButtons.css")
	$RemoveSTR       = [regex]::Escape('+" "+t.NLS_UNSUPPORTED')
	$CustomCCSLink   = '	<link rel="stylesheet" href="' + $CustomCCS + '"/>'

	if (isVSCodeNotPatched $CustomCCSLink) {
		$HTMLEditor  = Get-Content -Encoding UTF8 $VSCodeIndexHTML
		$HTMLEditor[$HTMLEditor.Count - 1] = $HTMLEditor[$HTMLEditor.Count - 1] -replace "</html>", ""
		$HTMLEditor += $CustomCCSLink
		$HTMLEditor += "</html>"
		$HTMLEditor | Out-File -Encoding UTF8 $VSCodeIndexHTML

		$JSEditor = (Get-Content -Encoding UTF8 $VSCodeMainJS) -replace $RemoveSTR, ""
		$JSEditor | Out-File -Encoding UTF8 $VSCodeMainJS
	}
}

function Update-VSCode {
	Get-VSKeys
	Get-VSSettings
	Get-VSTheme

	Get-VSCodePathed

	if ([System.Environment]::OSVersion.Platform -eq "Win32NT") {
		$obj = New-Object -ComObject WScript.Shell
		$link = $obj.CreateShortcut([io.path]::combine($env:APPDATA, "Microsoft", "Windows", "Start Menu", "Programs", "VSCode.lnk"))
		$link.TargetPath = [io.path]::combine("$ToolsLocation", "VSCode", "Code.exe")
		$link.Arguments = "-r"
		$link.Hotkey = "Alt+Ctrl+E"
		$link.Save()
	}

	Copy-Item -Force -Recurse ([IO.Path]::Combine($ToolsLocation, "Env", "vssettings", "my-editor")) ([IO.Path]::Combine($HOME, ".vscode", "extensions"))
}

Export-ModuleMember -Function Update-VSCode