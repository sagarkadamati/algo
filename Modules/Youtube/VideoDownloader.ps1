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

function VideoTS {
	$Link = "https://staragvodweb1-vh.akamaihd.net/i/videos/maatv/hhma/790/1000060685_,16,54,106,180,400,800,1300,2000,3000,4500,_STAR.mp4.csmil/master.m3u8?hdnea=st=1541752713~exp=1541754513~acl=/*~hmac=282f4ae95b777fc694cfd0eb2e08a247457fcc22f0ec4b6b0d592dbbae1e80bc"
	$outFile = "out.mp4"

	ffmpeg -user_agent "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_5) AppleWebKit/601.7.8 (KHTML, like Gecko) Version/9.1.3 Safari/537.86.7" -i $Link -c copy $outFile
}