$Global:DirectorySperator = [IO.Path]::DirectorySeparatorChar

function Setup {
	$PathSeperator = [IO.Path]::PathSeparator

	$Global:Workspace = Join-Path "$Home" "Workspace"
	$Global:Projects  = Join-Path "$Workspace" "Projects"
	$Global:Tools     = Join-Path "$Workspace" "Tools"
	$Global:Scripts   = Join-Path "$Tools" "Scripts"
	$Global:PSScriptsCommon = [IO.Path]::Combine("$Projects", "algos", "ps1", "Common")
	if ([System.Environment]::OSVersion.Platform -eq "Unix") {
		$Global:PSScriptsPlatfrom = [IO.Path]::Combine("$Projects", "algos", "ps1", "Unix")
	}
	else {
		$Global:PSScriptsPlatfrom = [IO.Path]::Combine("$Projects", "algos", "ps1", "Windows")
	}

	$Global:JAVA_HOME = [IO.Path]::Combine("$Tools", "Android", "Android Studio", "jre")

	$Global:GOROOT = "$Tools" + $DirectorySperator + "go"
	$Global:GOPATH = "$Projects" + $DirectorySperator + "algos" + $DirectorySperator + "go"

	## PATHS
	$GITPATH    = $(Join-Path $Tools "git"     | Join-Path -ChildPath "bin")
	$VSCODEPATH = $(Join-Path $Tools "VS Code" | Join-Path -ChildPath "bin")

	$KOTLINPATH = $(Join-Path $Tools "kotlinc" | Join-Path -ChildPath "bin")
	$PYTHONPATH = $(Join-Path $Tools "python"  | Join-Path -ChildPath "bin")

	$MYPATH     = $Scripts    + $PathSeperator
	$MYPATH    += $PSScriptsCommon + $PathSeperator + $PSScriptsPlatfrom + $PathSeperator

	$MYPATH    += $GOROOT     + $PathSeperator
	$MYPATH    += $GOPATH     + $PathSeperator
	$MYPATH    += $GITPATH    + $PathSeperator
	$MYPATH    += $VSCODEPATH + $PathSeperator
	$MYPATH    += $KOTLINPATH + $PathSeperator
	$MYPATH    += $PYTHONPATH + $PathSeperator
	$MYPATH    += $(Join-Path $JAVA_HOME "bin")  + $PathSeperator

	$env:PATH = $MYPATH + $env:PATH
}
function Work() {
	Set-Location $Workspace
}

function Proj($proj) {
	$setproj = $Projects + $DirectorySperator + $proj
	Set-Location $setproj
}
function Tool($tool) {
	$settool = $Tools + $DirectorySperator + $tool
	Set-Location $settool
}
function Script($script) {
	$setscript = $Scripts + $DirectorySperator + $script
	Set-Location $setscript
}

Setup
Work
