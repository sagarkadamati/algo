function Get-VSSettings {
	$jsondata  = Get-json $(Join-Path $PSScriptRoot "General.json")

	$jsondata | ConvertTo-Json
}