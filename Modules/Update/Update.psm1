function download($URI) {
	Invoke-WebRequest -Uri "$URI" -OutFile $($URI | Split-Path -Leaf)
}

function Update-Tools {
	download "https://dl.google.com/go/go1.10.3.linux-386.tar.gz"	

	download "https://github.com/JetBrains/kotlin/releases/download/v1.2.51/kotlin-compiler-1.2.51.zip"
	download "https://dl.google.com/go/go1.10.3.windows-amd64.zip"
	download "https://www.python.org/ftp/python/3.7.0/python-3.7.0-embed-amd64.zip"
}

function Get-OS {
	if ($([System.Environment]::OSVersion.Platform) -Like "Win32NT") {
		Write-Output "windows"
	}
	else {
		Write-Output "linux"
	}
}

Add-Type -AssemblyName System.IO.Compression.FileSystem
function Unzip
{
    param([string]$zipfile, [string]$outpath)

    [System.IO.Compression.ZipFile]::ExtractToDirectory($zipfile, $outpath)
}

function Update-KotlinTools {
	[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

	$request = Invoke-WebRequest -UseBasicParsing -Uri https://github.com/JetBrains/kotlin/releases

	$KotlinURL = ($request.Links | Where-Object href -Like "*kotlin-compiler-*.zip").href
	if ($($KotlinURL.Count) -ne 1) {
		$KotlinURL = $KotlinURL[0]
	}
	$Kotlin = $KotlinURL | Split-Path -Leaf

	$request = Invoke-WebRequest -UseBasicParsing -Uri https://github.com/JetBrains/kotlin-native/releases

	$NativeURL = ($request.Links | Where-Object href -Like "*kotlin-native-$(Get-OS)*.zip").href
	if ($($NativeURL.Count) -ne 1) {
		$NativeURL = $NativeURL[0]
	}
	$KotlinNative = $NativeURL | Split-Path -Leaf

	# Write-Host $KotlinURL
	# Write-Host $NativeURL

	pushd .
	$DownloadPath = $(Join-Path $ToolsLocation "download")
	New-Item -Type Directory $DownloadPath -Force -ErrorAction Ignore | Out-Null
	Set-Location $DownloadPath

	$KotlinRoot = $(Join-Path $ToolsLocation "Kotlin")
	New-Item -Type Directory $KotlinRoot -Force -ErrorAction Ignore | Out-Null

	if (!(Test-Path $Kotlin)) {
		Remove-Item "*kotlin-compiler-*.zip" -ErrorAction Ignore

		Write-Host -NoNewLine "Downloading Kotlin..."
		Invoke-WebRequest -Uri $("https://github.com" + $KotlinURL) -OutFile $Kotlin
		Write-Host "done"

		if (Test-Path $Kotlin) {
			Remove-Item -Recurse $(Join-Path $KotlinRoot "kotlinc") -ErrorAction Ignore
			Unzip $(Join-Path $DownloadPath $Kotlin) $KotlinRoot
		}
	}
	
	if (!(Test-Path $KotlinNative)) {
		Remove-Item "*kotlin-native-*.zip" -ErrorAction Ignore

		Write-Host -NoNewLine "Downloading Kotlin Native..."
		Invoke-WebRequest -Uri $("https://github.com" + $NativeURL) -OutFile $KotlinNative
		Write-Host "done"

		if (Test-Path $KotlinNative) {
			Remove-Item -Recurse $(Join-Path $KotlinRoot "kotlin-native") -ErrorAction Ignore
			Unzip $(Join-Path $DownloadPath $KotlinNative) $KotlinRoot
			Move-Item $(Join-Path $KotlinRoot $(Get-ChildItem -Path $KotlinRoot "kotlin-native*").Name) $(Join-Path $KotlinRoot "kotlin-native")
		}
	}
	popd
}

function Update-Env {
	$CDIR = Get-Location

	Env
	git pull

	Set-Location $CDIR
	SetupEnv
}

# Export-ModuleMember -Function Update-Env, Update-Tools