function Update-Paths {
	$PS = [IO.Path]::PathSeparator

	$Global:WorkspaceLocation  = Join-Path $Home              "Workspace"
	$Global:ProjectsLocation   = Join-Path $WorkspaceLocation "Projects"
	$Global:ToolsLocation      = Join-Path $WorkspaceLocation "Tools"
	$Global:ScriptsLocation    = [IO.Path]::Combine($ToolsLocation, "Env", "Scripts")

	$Global:GOROOT     = [IO.Path]::Combine($ToolsLocation,    "Go")
	$Global:GOPATH     = [IO.Path]::Combine($ProjectsLocation, "algos",   "go")
	$Global:JAVA_HOME  = [IO.Path]::Combine($ToolsLocation,    "Android", "Android Studio", "jre")

	$PYTHONPATH        = [IO.Path]::Combine($ToolsLocation, "Python")
	$GITPATH           = [IO.Path]::Combine($ToolsLocation, "Git",     "bin")
	$VSCODEPATH        = [IO.Path]::Combine($ToolsLocation, "VS Code", "bin")
	$KOTLINPATH        = [IO.Path]::Combine($ToolsLocation, "Kotlin", "kotlinc" , "bin")
	$KOTLINPATH       += $PS
	$KOTLINPATH       += [IO.Path]::Combine($ToolsLocation, "Kotlin", "kotlin-native", "bin")

	$WIN_FFMPEG        = [IO.Path]::Combine($ToolsLocation, "Env", "Tools", "ffmpeg", "bin")

	## Set Paths
	$MYPATH            = $ScriptsLocation              + $PS
	$MYPATH           += $GITPATH                      + $PS
	$MYPATH           += $VSCODEPATH                   + $PS
	$MYPATH           += $KOTLINPATH                   + $PS
	$MYPATH           += $PYTHONPATH                   + $PS
	$MYPATH           += $(Join-Path $GOROOT    "bin") + $PS
	$MYPATH           += $(Join-Path $GOPATH    "bin") + $PS
	$MYPATH           += $(Join-Path $JAVA_HOME "bin") + $PS

	if ($([System.Environment]::OSVersion.Platform) -Like "Win32NT") {
		$MYPATH           += $WIN_FFMPEG                   + $PS
	}

	$env:PATH          = $MYPATH + $env:PATH

	Set-Location $WorkspaceLocation
}

function Workspace() {
	Set-Location $WorkspaceLocation
}

function Projects() {
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
		$configurationProjects = Get-ChildItem -Directory -Path $ProjectsLocation | Select-Object -ExpandProperty Name
		$AttribColl.Add((New-Object  System.Management.Automation.ValidateSetAttribute($configurationProjects)))

		$RuntimeParam    = New-Object System.Management.Automation.RuntimeDefinedParameter('Name', [string], $AttribColl)

		$RuntimeParamDic = New-Object System.Management.Automation.RuntimeDefinedParameterDictionary
		$RuntimeParamDic.Add('Name', $RuntimeParam)

		return  $RuntimeParamDic
	}

	process
	{
		Set-Location $(Join-Path $ProjectsLocation $($PSBoundParameters.Name + ""))
	}
}

function Tools($tool) {
	Set-Location $(Join-Path $ToolsLocation $($tool + ""))
}

function Scripts($script) {
	Set-Location $(Join-Path $ScriptsLocation $($script + ""))
}

function Env {
	Set-Location $(Join-Path $ToolsLocation "Env")
}

New-Alias -Name proj -Value Projects
New-Alias -Name tls  -Value Tools
New-Alias -Name work -Value Workspace

Export-ModuleMember -Function Update-Paths, Workspace, Projects, Tools, Scripts, Env -Alias Proj, tls, work