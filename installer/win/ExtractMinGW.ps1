param(
    [Parameter()]
    [string]$Archive,
    [Parameter()]
    [string]$Dest
)
Expand-Archive -Force -Path $Archive -DestinationPath $Dest