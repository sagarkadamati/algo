function Get-VSKeys {
	$jsondata  = Get-json $(Join-Path $PSScriptRoot "DeRegister.json")
	$jsondata += Get-json $(Join-Path $PSScriptRoot "Cancel.json")
	$jsondata += Get-json $(Join-Path $PSScriptRoot "Cursor.json")
	$jsondata += Get-json $(Join-Path $PSScriptRoot "DeRegister.json")
	$jsondata += Get-json $(Join-Path $PSScriptRoot "Editor.json")
	$jsondata += Get-json $(Join-Path $PSScriptRoot "Explorer.json")
	$jsondata += Get-json $(Join-Path $PSScriptRoot "Git.json")
	$jsondata += Get-json $(Join-Path $PSScriptRoot "List.json")
	$jsondata += Get-json $(Join-Path $PSScriptRoot "Search.json")
	$jsondata += Get-json $(Join-Path $PSScriptRoot "Settings.json")
	$jsondata += Get-json $(Join-Path $PSScriptRoot "Tasks.json")
	$jsondata += Get-json $(Join-Path $PSScriptRoot "UI.json")

	$jsondata | ConvertTo-Json
}
