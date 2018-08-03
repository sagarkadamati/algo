function Get-YoutubeVideoID($youtubeURL) {
	$VideoID = [regex]::Match([regex]::Match([regex]::Match($youtubeURL,
			'(?:v|embed|watch\?v)(?:=|/)([^"&?/=%]{11})').Groups[0].Value,
			'(?:=|/)([^"&?/=%]{11})').Groups[0].Value,
			'([^"&?/=%]{11})').Groups[0].Value

	return $VideoID
}

function Get-YoutubeVideoInfo($VideoID) {
	$URL = "http://youtube.com/get_video_info?video_id=" + $VideoID

	$Response = invoke-WebRequest -uri $URL

	$Response.RawContent
}

function YoutubeParseVideoInfo($VideoInfo) {

}

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
		$VideoID   = Get-YoutubeVideoID $video
		$VideoInfo = Get-YoutubeVideoInfo $VideoID

		[System.Uri]$VideoInfo
	}
}

Export-ModuleMember -Function Youtube