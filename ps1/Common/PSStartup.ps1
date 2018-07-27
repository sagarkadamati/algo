. PSTheme.ps1
. PSPrompt.ps1
. PSUpdate.ps1
. PSTabCompletion.ps1

if (Test-Path $(Join-Path $PSPlatfromScripts "PSStartup.ps1")) {
	. $(Join-Path $PSPlatfromScripts "PSStartup.ps1")
}