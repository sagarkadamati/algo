function download($URI) {
	Invoke-WebRequest -Uri "$URI" -OutFile $($URI | Split-Path -Leaf)
}

function Update-Tools {
	download "https://dl.google.com/go/go1.10.3.linux-386.tar.gz"

	download "https://github.com/JetBrains/kotlin/releases/download/v1.2.51/kotlin-compiler-1.2.51.zip"
	download "https://dl.google.com/go/go1.10.3.windows-amd64.zip"
	download "https://www.python.org/ftp/python/3.7.0/python-3.7.0-embed-amd64.zip"
}
function Update-Env {
	$CDIR = Get-Location

	Env
	git pull

	Set-Location $CDIR
	SetupEnv
}

Export-ModuleMember -Function Update-Env, Update-Tools