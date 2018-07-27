function YoutubeGetURLs($youtubeURL) {
	if ($youtubeURL -like "*list=*") {
		$VideoUrls = $($(invoke-WebRequest -uri $youtubeURL).Links | Where-Object {$_.HREF -like "/watch*"} | Where-Object innerText -notmatch ".[0-9]:[0-9]." | Where-Object {$_.innerText.Length -gt 3} | Select-Object innerText,@{Name="URL";Expression={'http://www.youtube.com' + $_.href}} | Where-Object innerText -notlike "*Play all*").URL

		return $VideoUrls
	}
	return $youtubeURL
}

function Youtube($URL) {
	$VideoUrls = YoutubeGetURLs($URL)
	ForEach ($video in $VideoUrls) {
		$video
	}
}

Export-ModuleMember -Function Youtube