param(
	[Switch]$Build,
	[String]$FileName
)

$env:PSModulePath = "C:\Users\Sagar\Workspace\Tools\Env\Modules;$env:PSModulePath"
SetupEnv

if ($FileName -match "Kotlin/Projects/*") {
	$Project = $(($FileName -replace "Kotlin/Projects/", "") -split '/')[0]
	if ($Build) {
		kt -Build $Project
	}
	else {
		kt $Project
	}
}
else {
	Write-Host "No Project Support"
}