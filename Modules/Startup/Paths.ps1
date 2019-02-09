function Update-Paths {
	$PS = [IO.Path]::PathSeparator

	$Global:WorkspaceLocation  = Join-Path $Home              "Workspace"
	$Global:ProjectsLocation   = Join-Path $WorkspaceLocation "Projects"
	$Global:ToolsLocation      = Join-Path $WorkspaceLocation "Tools"
	$Global:ModulesLocation    = [IO.Path]::Combine($ToolsLocation, "Env", "Modules")

	$Global:GOROOT     = [IO.Path]::Combine($ToolsLocation,    "Go")
	$Global:GOPATH     = [IO.Path]::Combine($ProjectsLocation, "algos",   "go")
	$Global:JAVA_HOME  = [IO.Path]::Combine($ToolsLocation,    "Android", "Studio", "jre")

	$PYTHONPATH        = [IO.Path]::Combine($ToolsLocation, "Python")
	$GITPATH           = [IO.Path]::Combine($ToolsLocation, "Git",     "bin")
	$GITPATH          += $PS + [IO.Path]::Combine($ToolsLocation, "Git", "usr", "bin")
	$VSCODEPATH        = [IO.Path]::Combine($ToolsLocation, "VSCode", "bin")
	$KOTLINPATH        = [IO.Path]::Combine($ToolsLocation, "Kotlin", "kotlinc" , "bin")
	$KOTLINPATH       += $PS
	$KOTLINPATH       += [IO.Path]::Combine($ToolsLocation, "Kotlin", "kotlin-native", "bin")

	$WIN_FFMPEG        = [IO.Path]::Combine($ToolsLocation, "Env", "Tools", "ffmpeg", "bin")

	## Set Paths
	$MYPATH            = $ModulesLocation              + $PS
	$MYPATH           += $GITPATH                      + $PS
	$MYPATH           += $VSCODEPATH                   + $PS
	$MYPATH           += $KOTLINPATH                   + $PS
	$MYPATH           += $PYTHONPATH                   + $PS
	$MYPATH           += $(Join-Path $GOROOT    "bin") + $PS
	$MYPATH           += $(Join-Path $GOPATH    "bin") + $PS
	$MYPATH           += $(Join-Path $JAVA_HOME "bin") + $PS

	if ($([System.Environment]::OSVersion.Platform) -Like "Win32NT") {
		$MYPATH       += $WIN_FFMPEG                   + $PS
	}

	$env:PATH          = $MYPATH + $env:PATH
	if ([System.Environment]::OSVersion.Platform -NotLike "Win32NT") {
		$env:APPDATA       = $(Join-Path $HOME ".config")
	}

	Set-Location $WorkspaceLocation
}
