function Get-YoutubeVideoID($youtubeURL) {
	$VideoID = [regex]::Match([regex]::Match([regex]::Match($youtubeURL,
			'(?:v|embed|watch\?v)(?:=|/)([^"&?/=%]{11})').Groups[0].Value,
			'(?:=|/)([^"&?/=%]{11})').Groups[0].Value,
			'([^"&?/=%]{11})').Groups[0].Value

	return $VideoID
}

function Get-YoutubeVideoInfo($VideoURL) {
	$VideoID = Get-YoutubeVideoID $VideoURL

	$URL = "http://youtube.com/get_video_info?video_id=" + $VideoID

	invoke-WebRequest -Uri $URL -OutFile videoinfo.txt
}

function Remove-InvalidFileNameChars {
	param(
	  [Parameter(Mandatory=$true,
		Position=0,
		ValueFromPipeline=$true,
		ValueFromPipelineByPropertyName=$true)]
	  [String]$Name
	)

	$invalidChars = [IO.Path]::GetInvalidFileNameChars() -join ''
	$re = "[{0}]" -f [RegEx]::Escape($invalidChars)
	return ($Name -replace $re)
}

function Get-YoutubeParseVideoInfo {
	# [System.Web.HttpUtility]::UrlDecode($(Get-Content videoinfo.txt))

	$answer = [System.Web.HttpUtility]::ParseQueryString($(Get-Content videoinfo.txt))
	$streams = $answer["url_encoded_fmt_stream_map"] -split ','

	$StreamList = @()

	$index = 0
	foreach ($stream in $streams) {
		$ListInfo = New-Object 'system.collections.generic.dictionary[string, string]'

		$videoinfo = [System.Web.HttpUtility]::ParseQueryString($stream)

		$ListInfo["index"] = $index++
		$ListInfo["url"] = $videoinfo["url"]
		$ListInfo["title"] = Remove-InvalidFileNameChars $answer["title"]
		# $ListInfo["title"] = $videoinfo["title"]
		$ListInfo["quality"] = $videoinfo["quality"]
		$ListInfo["type"] = $videoinfo["type"]
		$ListInfo["author"] = $videoinfo["author"]
		$ListInfo["sig"] = $videoinfo["sig"]
		$ListInfo["extension"] = $(($ListInfo["type"] -split ';')[0] -split '/')[1]
		$ListInfo["filename"] = $ListInfo["title"] + "." + $ListInfo["extension"]

		$StreamList += $ListInfo
	}

	return $StreamList
}

function YoutubeGetURLs($youtubeURL) {
	if ($youtubeURL -like "*list=*") {
		$VideoUrls = $($(invoke-WebRequest -uri $youtubeURL).Links | Where-Object {$_.HREF -like "/watch*"} | Where-Object innerText -notmatch ".[0-9]:[0-9]." | Where-Object {$_.innerText.Length -gt 3} | Select-Object innerText,@{Name="URL";Expression={'http://www.youtube.com' + $_.href}} | Where-Object innerText -notlike "*Play all*").URL

		return $VideoUrls
	}
	return $youtubeURL
}

function Youtube {
	param (
		[Switch]$List,
		[String]$URL,
		[Int]$Index
	)

	process {
		$VideoUrls = YoutubeGetURLs($URL)
		ForEach ($video in $VideoUrls) {
			Get-YoutubeVideoInfo $video
			$Streams = Get-YoutubeParseVideoInfo
			
			if($List)
			{
				$streams
			}
			else
			{
				if ($Index) {
					invoke-WebRequest -Uri $streams[$Index]["url"] -OutFile $streams[0]["filename"]
				}
				else {
					invoke-WebRequest -Uri $streams[0]["url"] -OutFile $streams[0]["filename"]
				}
			}
		}

		if(Test-Path .\videoinfo.txt) {
			Remove-Item .\videoinfo.txt
		}
	}
}

Export-ModuleMember -Function Youtube