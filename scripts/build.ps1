param(
	[Switch]$Build,
	[String]$FileName
)

$env:PSModulePath = "~\Workspace\Tools\Env\Modules;$env:PSModulePath"
SetupEnv
env

if ($FileName -match "Kotlin/Projects/*") {
	$Project = $(($FileName -replace "Kotlin/Projects/", "") -split '/')[0]
	if ($Build) {
		kt -Build $Project
		if (Test-Path "Kotlin/Run/${Project}.jar") {
			kt $Project
		}
	}
	else {
		kt $Project
	}
}
else {
	Write-Host "No Project Support"
}