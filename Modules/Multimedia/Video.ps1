function CreateDirectory($dir) {
	New-Item -ItemType Directory -Force -Path $dir | Out-Null
}

function AutoCropVideos($Encoding, [Switch]$Aspect, [Switch]$NoCRF) {
	$PYCrop = $([IO.Path]::Combine($ToolsLocation, "Env", "python", "Projects", "PyCrop.py"))
	$Files  = Get-FileNames -Recursive ".mp4$|.mkv$|.avi$" | Select-String  -NotMatch "^HEVC|^H.264"

	$PixelFormat    = "yuv420p"
	$AspectRatio    = "16:9"
	$StartTime      = "00:00:00"
	$EndTime        = ""

	$VideoCodec     = "hevc"
	$OUT            = "HEVC"
	$CRF            = 23

	if ($Encoding -Like "h264") {
		$VideoCodec = $Encoding
		$OUT        = "H.264"
		$CRF        = 18
	}
	else {
		$VideoCodec = "hevc"
		$OUT        = "HEVC"
		$CRF        = 23
	}

	CreateDirectory $OUT
	$TMPFile = $(Join-Path $OUT "tmp.mp4")
	foreach($File in $Files) {
		CreateDirectory $(Join-Path $OUT $($File -replace $(Split-Path $File -Leaf), ""))

		if (($File -notlike "*HEVC*") -and ($File -notlike "*H.264*")) {
			if (!$(Test-Path $(Join-Path $OUT $File))) {
				$Crop = python $PYCrop $File
				$VideoFilter    = "$Crop"

				# $Fno = [Int]($(Split-Path $File -Leaf)).split(' ')[0]

				$TMPFile = Join-Path $OUT $(($File -replace ".mkv",".mp4") -replace ".avi",".mp4")
				Write-Host "$File : $Crop"
				if (!$(Test-Path $TMPFile)) {
					if ($Encoding -Like "copy") {
						if ($EndTime -Like "*:*:*") {
							ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -to $EndTime -c copy $TMPFile
						}
						else {
							ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -c copy $TMPFile
						}
					}
					else {
						if ($EndTime -Like "*:*:*") {
							# ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -to $EndTime -crf $CRF -filter:v "$VideoFilter" -aspect $AspectRatio -strict -2 -c:v "$VideoCodec" -pix_fmt "$PixelFormat" -c:a copy $TMPFile
							# ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -to $EndTime -crf $CRF $TMPFile

							# ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -to $EndTime -filter:v "$VideoFilter" -crf $CRF -maxrate 1M -bufsize 2M -c:v "$VideoCodec" -c:a copy -x265-params pass=1 -an -f mp4 NUL
							# ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -to $EndTime -filter:v "$VideoFilter" -crf $CRF -maxrate 1M -bufsize 2M -c:v "$VideoCodec" -c:a copy -x265-params pass=2 -f mp4 $TMPFile

							if ($NoCRF) {
								if ($Aspect) {
									# ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -to $EndTime -filter:v "$VideoFilter" -aspect $AspectRatio -strict -2 -crf $CRF -c:v "$VideoCodec" -c:a copy -an -f mp4 NUL
									ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -to $EndTime -filter:v "$VideoFilter" -aspect $AspectRatio -strict -2 -q:v 0 -c:v "$VideoCodec" -c:a copy -f mp4 $TMPFile
								}
								else {
									ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -to $EndTime -filter:v "$VideoFilter" -q:v 0 -c:v "$VideoCodec" -c:a copy -f mp4 $TMPFile
								}
							}
							else {
								if ($Aspect) {
									# ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -to $EndTime -filter:v "$VideoFilter" -aspect $AspectRatio -strict -2 -crf $CRF -c:v "$VideoCodec" -c:a copy -an -f mp4 NUL
									ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -to $EndTime -filter:v "$VideoFilter" -aspect $AspectRatio -strict -2 -crf $CRF -c:v "$VideoCodec" -c:a copy -f mp4 $TMPFile
								}
								else {
									ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -to $EndTime -filter:v "$VideoFilter" -crf $CRF -c:v "$VideoCodec" -c:a copy -f mp4 $TMPFile
								}
							}
						}
						else {
							if ($NoCRF) {
								if ($Aspect) {
									# ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -filter:v "$VideoFilter" -aspect $AspectRatio -strict -2 -crf $CRF -c:v "$VideoCodec" -c:a copy -an -f mp4 NUL
									ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -filter:v "$VideoFilter" -aspect $AspectRatio -strict -2 -q:v 0 -c:v "$VideoCodec" -c:a copy -f mp4 $TMPFile
								}
								else {
									ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -filter:v "$VideoFilter" -q:v 0 -c:v "$VideoCodec" -c:a copy -f mp4 $TMPFile
								}
							}
							else {
								if ($Aspect) {
									# ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -filter:v "$VideoFilter" -aspect $AspectRatio -strict -2 -crf $CRF -c:v "$VideoCodec" -c:a copy -an -f mp4 NUL
									ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -filter:v "$VideoFilter" -aspect $AspectRatio -strict -2 -crf $CRF -c:v "$VideoCodec" -c:a copy -f mp4 $TMPFile
								}
								else {
									ffmpeg -hide_banner -y -v error -stats -i $File -ss $StartTime -filter:v "$VideoFilter" -crf $CRF -c:v "$VideoCodec" -c:a copy -f mp4 $TMPFile
								}
							}
						}
					}
				}
			}
		}
	}
}

# x265 [info]: tools: rd=3 psy-rd=2.00 rskip signhide tmvp strong-intra-smoothing
# x265 [info]: tools: deblock sao

# x265 [info]: tools: rd=4 psy-rd=2.00 rskip signhide tmvp strong-intra-smoothing
# x265 [info]: tools: deblock sao
# x265 [info]: tools: rect limit-modes rdoq=2 psy-rdoq=1.00

function TrimVideos {
	if (Test-Path "trim.txt") {
		$TrimVideos = Get-Content -Encoding UTF8 .\trim.txt
		foreach ($TrimData in $TrimVideos) {
			$DataLine  = $TrimData.Split('|')
			$VideoFile = ($DataLine[0]).Trim()
			$VTimes    = ($DataLine[1]).Split(',')
			$CName     = $DataLine[2]
			$OUT       = (Join-Path "HEVC" $($VideoFile -replace ".mp4", ""))
			$Count     = 0
			$Digits    = 1

			$TCount    = $VTimes.Split('-').Length
			while($TCount -ne 0) {
				$TCount = [Math]::Abs($TCount / 10)
				$Digits++

				if ($TCount -ge 10) { continue } else { break }
			}

			foreach($VTime in $VTimes) {
				$TrimTime  = $VTime.Split('-')
				$StartTime = "00:00:00"
				$EndTime   = ($TrimTime[0] + "").Trim()

				foreach($NewEndTime in $TrimTime[1..$TrimTime.Length]) {
					$StartTime = $EndTime
					$EndTime   = ($NewEndTime + "").Trim()

					switch -Wildcard ($StartTime) {
						'[0-9][0-9]:[0-9][0-9]:[0-9][0-9]' { }
						'[0-9][0-9]:[0-9][0-9]:[0-9]'      { $StartTime = "0" + $StartTime }
						'[0-9][0-9]:[0-9][0-9]'            { $StartTime = "00:" + $StartTime }
						'[0-9]:[0-9][0-9]'                 { $StartTime = "00:0" + $StartTime }
						'[0-9][0-9]'                       { $StartTime = "00:00:" + $StartTime }
						'[0-9]'                            { $StartTime = "00:00:0" + $StartTime }
						default                            { $StartTime = "00:00:00"}
					}

					switch -Wildcard ($EndTime) {
						'[0-9][0-9]:[0-9][0-9]:[0-9][0-9]' { }
						'[0-9][0-9]:[0-9][0-9]:[0-9]'      { $EndTime = "0" + $EndTime }
						'[0-9][0-9]:[0-9][0-9]'            { $EndTime = "00:" + $EndTime }
						'[0-9]:[0-9][0-9]'                 { $EndTime = "00:0" + $EndTime }
						'[0-9][0-9]'                       { $EndTime = "00:00:" + $EndTime }
						'[0-9]'                            { $EndTime = "00:00:0" + $EndTime }
						default                            { }
					}

					$OUTFile   = $($([String]++$Count) | % PadLeft $Digits '0')
					if ($CName) {
						$OUTFile += " " + ($CName).Trim()
					}
					$OUTFile  += ".mp4"
					$OUTFile   = ($(Split-Path -Leaf $VideoFile) -replace ".mp4","") + " " + $OUTFile
					$OUTFile   = Join-Path $OUT $OUTFile

					CreateDirectory $OUT
					if (!$(Test-Path $OUTFile)) {
						if ($EndTime -Like '[0-9][0-9]:[0-9][0-9]:[0-9][0-9]') {
							# Write-Host "ffmpeg -hide_banner -y -v error -stats -i $VideoFile -ss $StartTime -to $EndTime -c copy $OUTFile"
							# ffmpeg -hide_banner -y -v error -stats -i $VideoFile -ss $StartTime -to $EndTime -c copy $OUTFile
							ffmpeg -hide_banner -y -v error -stats -i $VideoFile -ss $StartTime -to $EndTime -crf 23 -c:v hevc -c:a copy $OUTFile
						}
						else {
							# Write-Host "ffmpeg -hide_banner -y -v error -stats -i $VideoFile -ss $StartTime -to $EndTime -c copy $OUTFile"
							# ffmpeg -hide_banner -y -v error -stats -i $VideoFile -ss $StartTime -c copy $OUTFile
							ffmpeg -hide_banner -y -v error -stats -i $VideoFile -ss $StartTime -crf 23 -c:v hevc -c:a copy $OUTFile
						}
					}
				}
			}
		}
	}
}

	# foreach ($Video in $Videos) {
	# 	$FileName = $Video.FullName
	# 	CreateDirectory $(Join-Path "out" $((Get-ChildItem $FileName).Directory).Name))

	# 	if (!$(Test-Path $(Join-Path "out" "$Video"))) {
	# 		$Crop = python $PYCrop $Video
	# 		Write-Host "$Video.Name : $Crop"

	# 		$VideoFilter = "$Crop"
	# 		# $VideoFilter = "$Crop, scale=512:288"
	# 		# $VideoFilter = "$Crop, scale=640:360"

	# 		$VideoCodec = "hevc"

	# 		# $PixelFormat  = "yuv420p10le"
	# 		$PixelFormat  = "yuv420p"

	# 		$Fno = [Int]($Video).split(' ')[0]
	# 		if ($Fno -le 107) {
	# 			$StartTime = "00:01:08"
	# 			$EndTime = ""
	# 		}
	# 		else {
	# 			$StartTime = "00:00:05"
	# 			$EndTime = ""
	# 		}

	# 		ffmpeg -hide_banner -y -v error -stats -i $Video.Name -ss $StartTime -crf 23 -filter:v "$VideoFilter" -aspect 16:9 -strict -2 -c:v "$VideoCodec" -pix_fmt "$PixelFormat" -preset:v veryslow -c:a copy $(Join-Path "out" "$Video.Name")

	# 		# ffmpeg -hide_banner -y -v error -stats -i $Video -filter:v "$VideoFilter" -c:v "$VideoCodec" -c:a copy $(Join-Path "out" "$Video")
	# 		# ffmpeg -hide_banner -y -v error -stats -i $Video -ss $StartTime -filter:v "$VideoFilter" -aspect 16:9 -strict -2 -c:v "$VideoCodec" -pix_fmt "$PixelFormat" -preset:v veryslow -c:a copy $(Join-Path "out" "$Video")
	# 		# ffmpeg -hide_banner -y -v error -stats -i $Video -ss $StartTime -b:v 400k -filter:v "$VideoFilter" -aspect 16:9 -strict -2 -c:v "$VideoCodec" -pix_fmt "$PixelFormat" -c:a copy $(Join-Path "out" "$Video")
	# 		# ffmpeg -hide_banner -y -v error -stats -i $Video -filter:v "$VideoFilter" -c:v "$VideoCodec" -pix_fmt "$PixelFormat" -crf 0 -c:a copy $($(Join-Path "out" "$Video") -replace "DAT", "mp4")

	# 		# ffmpeg -hide_banner -y -v error -stats -i $Video -pix_fmt "$PixelFormat" -crf 22 -filter:v "$VideoFilter" -c:v "$VideoCodec" -x265-params pass=1 -an -f mp4 NUL
	# 		# ffmpeg -hide_banner -y -v error -stats -i $Video -pix_fmt "$PixelFormat" -crf 22 -filter:v "$VideoFilter" -c:v "$VideoCodec" -x265-params pass=2 -c:a copy $(Join-Path "out" "$Video")

	# 		# ffmpeg -hide_banner -y -v error -stats -i $Video -filter:v "$Crop, scale=512:288" -c:a copy $(Join-Path "out" "$Video")

	# 		# ffmpeg -hide_banner -i input \
	# 		# 	-c:v libx265 -pix_fmt yuv420p \
	# 		# 	-x265-params crf=28:keyint=240:min-keyint=20 \
	# 		# 	-preset:v slow \
	# 		# 	-c:a libfdk_aac -vbr 4 \
	# 		# 	output.mp4

	# 		# ffmpeg -hide_banner -i '.\Part 1.DAT' -c:v libx265 -pix_fmt yuv420p -x265-params crf=28:keyint=240:min-keyint=20 -preset:v slow -c:a copy -vbr 4 '.\out\Part 1.mp4'
	# 	}
	# }

# old = crop=472:256:84:64
# new = crop=472:272:84:44

function ConcatVideos($OutFile) {
	if (Test-Path "concat.txt") {
		$CONCATSTR = """concat:"
		$count = 0;

		$Files = Get-Content -Encoding UTF8 "concat.txt"
		foreach ($file in $Files) {
			if ($count -ne 0) {
				$CONCATSTR += "|$file"
			} else {
				$CONCATSTR += "$file"
			}
			$count++;
		}
		$CONCATSTR += """"

		if ($OutFile) {
			echo ffmpeg -y -i "${CONCATSTR}" -c copy "${Outfile}"
		} else {
			ffmpeg -y -i ${CONCATSTR} -c copy out.mkv
		}
	}
}