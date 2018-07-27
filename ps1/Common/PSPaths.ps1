$Global:DirectorySperator = [IO.Path]::DirectorySeparatorChar

Function Create-Directory($dir) {
	if (!$(Test-Path Tools))
	{
		New-Item -Type Directory $dir
	}
}

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

	$Global:GOROOT = "$Tools" + $DirectorySperator + "Go"
	$Global:GOPATH = "$Projects" + $DirectorySperator + "algos" + $DirectorySperator + "go"

	## PATHS
	$GITPATH    = $(Join-Path $Tools "Git"     | Join-Path -ChildPath "bin")
	$VSCODEPATH = $(Join-Path $Tools "VS Code" | Join-Path -ChildPath "bin")

	$KOTLINPATH = $(Join-Path $Tools "Kotlinc" | Join-Path -ChildPath "bin")
	$PYTHONPATH = $(Join-Path $Tools "Python"  | Join-Path -ChildPath "bin")

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
function Workspace() {
	Set-Location $Workspace
}

function Proj() {
	[OutputType([System.IO.FileInfo])]
	[CmdletBinding()]

	param()

	DynamicParam
	{
		$ParamAttrib = New-Object System.Management.Automation.ParameterAttribute
		# $ParamAttrib.Mandatory = $true
		$ParamAttrib.ParameterSetName = '__AllParameterSets'

		$AttribColl = New-Object  System.Collections.ObjectModel.Collection[System.Attribute]
		$AttribColl.Add($ParamAttrib)
		$configurationProjects = Get-ChildItem -Directory -Path $Projects | Select-Object -ExpandProperty Name
		$AttribColl.Add((New-Object  System.Management.Automation.ValidateSetAttribute($configurationProjects)))

		$RuntimeParam    = New-Object System.Management.Automation.RuntimeDefinedParameter('Name', [string], $AttribColl)

		$RuntimeParamDic = New-Object System.Management.Automation.RuntimeDefinedParameterDictionary
		$RuntimeParamDic.Add('Name', $RuntimeParam)

		return  $RuntimeParamDic
	}

	process
	{
		Set-Location $(Join-Path $Projects $PSBoundParameters.Name)
	}
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
Workspace
