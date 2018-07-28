$MODULESPATH = [IO.Path]::Combine($HOME, "Workspace","Tools","Env", "Modules")

function Setup {
	$CLOC = Get-Location
	if (!$(Test-Path $MODULESPATH))
	{
		New-Item -Type Directory -Force $($MODULESPATH + "../../..") | Out-Null
		Set-Location $($MODULESPATH + "../../..")
		git clone https://github.com/sagarkadamati/algos Env
		NightTheme
	}
	Set-Location $CLOC
}

function UpdateProfile {
	"`$env:PSModulePath =" + " `"" + $MODULESPATH + [IO.Path]::PathSeparator + "`$env:PSModulePath`""
	Write-Output "SetupEnv"	
}

Setup
UpdateProfile > $PROFILE
