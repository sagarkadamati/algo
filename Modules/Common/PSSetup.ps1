. $([IO.Path]::combine("$Home", "Workspace", "Projects", "algos", "ps1", "Common", "PSPaths.ps1"))

Function LoadModule($Module) {
	$MScript = $(Join-Path $Module ".ps1")
	$PlatfromScript = $(Join-Path $PSPlatfromScripts $MScript)

	. "$MScript"
	if (Test-Path $PlatfromScript) {
		. "$PlatfromScript"
	}
}

LoadModule "PSStartup"