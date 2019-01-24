# https://api.hotstar.com/h/v1/play
# https://api.hotstar.com/h/v1/play?contentId=1000007604&tas=5
# https://api.hotstar.com/o/v1/episode/detail?id=54812&contentId=1000007605&offset=0&size=20&tao=0&tas=5

https://api.hotstar.com/h/v1/play
video_id,
headers={'hotstarauth': auth,'x-country-code': 'IN','x-platform-code': 'JIO',},
query={query_name: video_id,'tas': 10000,}

https://ma312-r.analytics.edgekey.net/9.gif
?
a=S
~b=3d289801d10d617074
~c=ec35e896-6f11-4861-9355-da9f920cec68
~d=67e348f5-4910-4708-be68-0a792dba33eb
~e=1
~g=0
~w=6950
~ac=tv/master.m3u8
~ag=www.hotstar.com
~ah=-
~al=Windows
~am=L
~aw=https://hses.akamaized.net/videos/bharat/mhsbe/23_3ce35c2bc1/tv/master.m3u8
?
hdnea=
st=1547233423
~exp=1547235223
~acl=/*
~hmac=0eeb94daee6bd6eb1e6c168e6df515e75fc97e3427f5597f9feddddedb8a9093
~ax=O
~ay=CoreLibrary-4.16.25:HTML5Loader-1.3.12
~cg=Mythology
~cm=
~dx=6.942
~en=Dronacharya%27s%20Odd%20Demand
~pd=HS-WEB-PLAYER
~sa=Desktop
~sh=Divya%20Ravivaar:%20Mahabharat
~m=I
~v=0
~aa=hses.akamaized.net
~ap=161
~aq=2557360
~ft=1
~gb=
~tt=Dronacharya%27s%20Odd%20Demand
~va=1
~_cd_4738=6.7.0


https://api.hotstar.com/h/v1/play?contentId=1000226706
https://api.hotstar.com/h/v1/play?contentId=1000226706
https://ma312-r.analytics.edgekey.net/9.gif?a=I~b=3d289801d10d617074~c=d98c9396-2162-4ed1-b4c5-c8c53e5a9ffa~d=67e348f5-4910-4708-be68-0a792dba33eb~e=0~g=0~w=5~ag=www.hotstar.com~ah=-~al=Windows~ax=O~ay=CoreLibrary-4.16.25:HTML5Loader-1.3.12~cg=Mythology~cm=~dx=0.005~en=Arjun%20Faces%20Humiliation~pd=HS-WEB-PLAYER~sa=Desktop~sh=Divya%20Ravivaar:%20Mahabharat~ai=Mozilla/5.0%20(Windows%20NT%2010.0;%20Win64;%20x64)%20AppleWebKit/537.36%20(KHTML,%20like%20Gecko)%20Chrome/71.0.3578.98%20Safari/537.36~at=Chrome%2071~az=1.3~os=Windows-10~pr=-~pu=https://www.hotstar.com/tv/divya-ravivaar-mahabharat/s-1591/arjun-faces-humiliation/1000226706~_cd_4738=6.7.0
https://ma312-r.analytics.edgekey.net/9.gif?a=S~b=3d289801d10d617074~c=d98c9396-2162-4ed1-b4c5-c8c53e5a9ffa~d=67e348f5-4910-4708-be68-0a792dba33eb~e=1~g=0~w=935~ac=tv/master.m3u8~ag=www.hotstar.com~ah=-~al=Windows~am=L~aw=https://hses.akamaized.net/videos/bharat/mhsbe/22_1b452b3129/tv/master.m3u8?hdnea=st=1547278543~exp=1547280343~acl=/*~hmac=fc913f54fcadeda06e32f90ebf581c9b0f7e7ccc7366805acbc83712cf010893~ax=O~ay=CoreLibrary-4.16.25:HTML5Loader-1.3.12~cg=Mythology~cm=~dx=0.927~en=Arjun%20Faces%20Humiliation~pd=HS-WEB-PLAYER~sa=Desktop~sh=Divya%20Ravivaar:%20Mahabharat~m=I~v=365016.468~aa=hses.akamaized.net~ap=150~aq=2502680~ft=1~gb=~tt=Arjun%20Faces%20Humiliation~va=1~_cd_4738=6.7.0
https://ma312-r.analytics.edgekey.net/9.gif?a=P~b=3d289801d10d617074~c=d98c9396-2162-4ed1-b4c5-c8c53e5a9ffa~d=67e348f5-4910-4708-be68-0a792dba33eb~e=2~g=0~w=5944~ac=tv/master.m3u8~ag=www.hotstar.com~ah=-~al=Windows~am=L~aw=https://hses.akamaized.net/videos/bharat/mhsbe/22_1b452b3129/tv/master.m3u8?hdnea=st=1547278543~exp=1547280343~acl=/*~hmac=fc913f54fcadeda06e32f90ebf581c9b0f7e7ccc7366805acbc83712cf010893~ax=O~ay=CoreLibrary-4.16.25:HTML5Loader-1.3.12~bb=~cg=Mythology~cm=~dx=5.008~en=Arjun%20Faces%20Humiliation~pd=HS-WEB-PLAYER~sa=Desktop~sh=Divya%20Ravivaar:%20Mahabharat~m=PL~u=~v=369970.29099999997~x=5007~y=4953.822999999975~z=0~aa=hses.akamaized.net~ap=150~aq=2502680~da=0~dc=~dd=0~de=0~dg=0~dv=1~fb=0~fd=0~fe=0~fi=~fk=~fl=0:5007~gb=~rs=~tt=Arjun%20Faces%20Humiliation~_cd_4738=6.7.0


function Get-HotStarVideoID($HotStarURL) {
	# https://api.hotstar.com/h/v1/play?contentId=1000007608
	$VideoID = [regex]::Match([regex]::Match([regex]::Match($HotStarURL,
			'(?:v|embed|watch\?v)(?:=|/)([^"&?/=%]{11})').Groups[0].Value,
			'(?:=|/)([^"&?/=%]{11})').Groups[0].Value,
			'([^"&?/=%]{11})').Groups[0].Value

	return $VideoID
}

function Get-HotStarVideoInfo($VideoURL) {
	$VideoID = Get-HotStarVideoID $VideoURL

	$URL = "http://HotStar.com/get_video_info?video_id=" + $VideoID

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

function Get-HotStarParseVideoInfo {
	# [System.Web.HttpUtility]::UrlDecode($(Get-Content videoinfo.txt))
	Add-Type -AssemblyName System.Web
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

function HotStarGetURLs($HotStarURL) {
	if ($HotStarURL -like "*list=*") {
		$VideoUrls = $($(invoke-WebRequest -uri $HotStarURL).Links | Where-Object {$_.HREF -like "/watch*"} | Where-Object innerText -notmatch ".[0-9]:[0-9]." | Where-Object {$_.innerText.Length -gt 3} | Select-Object innerText,@{Name="URL";Expression={'http://www.HotStar.com' + $_.href}} | Where-Object innerText -notlike "*Play all*").URL
		# $VideoUrls = $($(Invoke-RestMethod $HotStarURL).Links | Where-Object {$_.HREF -like "/watch*"} | Where-Object innerText -notmatch ".[0-9]:[0-9]." | Where-Object {$_.innerText.Length -gt 3} | Select-Object innerText,@{Name="URL";Expression={'http://www.HotStar.com' + $_.href}} | Where-Object innerText -notlike "*Play all*").URL

		return $VideoUrls
	}
	return $HotStarURL
}

function HotStar {
	param (
		[Switch]$List,
		[String]$URL,
		[Int]$Index
	)

	process {
		$NOS = 1
		$VideoUrls = HotStarGetURLs($URL)
		# [array]::Reverse($VideoUrls)
		ForEach ($video in $VideoUrls) {
			Get-HotStarVideoInfo $video
			$Streams = Get-HotStarParseVideoInfo
			
			if($List)
			{
				$streams.type
			}
			else
			{
				$OUTFILE = "$NOS "
				if ($Index) {
					$OUTFILE += $streams[$Index]["filename"]
					if (!(Test-Path $OUTFILE)) {
						$OUTFILE
						invoke-WebRequest -Uri $($streams[$Index]["url"] + $streams[$Index]["sig"]) -OutFile $OUTFILE
					}
				}
				else {
					$OUTFILE += $streams[0]["filename"]
					if (!(Test-Path $OUTFILE)) {
						$OUTFILE
						invoke-WebRequest -Uri $($streams[0]["url"] + $streams[$Index]["sig"]) -OutFile $OUTFILE
					}
				}
				# $Streams
			}

			$NOS++
		}

		if(Test-Path .\videoinfo.txt) {
			Remove-Item .\videoinfo.txt
		}
	}
}

Export-ModuleMember -Function HotStar