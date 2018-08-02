function VideoDownload {
	$outdir = "c:\temp\VOD"
	$baseUrl = "http://someserver.com/asset/video/"
	cd $outdir
	$i = 1000

	do {
		$url = "$baseUrl/video_1464285826-2_$($i.ToString("00000")).ts"
		Write-Host "downloading file $($i.ToString("00000"))..." -nonewline
		try { Invoke-WebRequest $url -OutFile "$outdir\$($i.ToString("00000")).ts" -PassThru -ErrorAction Stop | Tee-Object -Variable request | Out-Null}
		catch{
			write-warning 'File not found or other error'
			break
		}

		write-host "[OK]"
		Start-Sleep -Seconds 2
		$i++
	} until ($request.StatusCode -ne 200)
}
