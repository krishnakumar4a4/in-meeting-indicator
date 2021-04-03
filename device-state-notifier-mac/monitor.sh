#!/bin/bash

echo "Base URL configured: $BASE_URL"

function updateMicStatus() {
	if [ $1 -eq 0 ]; then
		curl -X PUT "$BASE_URL/mic?state=on"
		echo "mic status updated to on"
	else
		curl -X PUT "$BASE_URL/mic?state=off"
		echo "mic status updated to off"
	fi
}

function updateCameraStatus() {
	if [ $1 -eq 0 ]; then
		curl -X PUT "$BASE_URL/camera?state=on"
		echo "camera status updated to on"
	else
		curl -X PUT "$BASE_URL/camera?state=off"
		echo "camera status updated to off"
	fi
}

cat "/System/Volumes/Data/Users/krishnak/Library/Application Support/Objective-See/OverSight/OverSight.log" | grep "Audio Device" | tail -n 1 | grep -q -w "active"
AUDIO_INIT_STATUS=$?
cat "/System/Volumes/Data/Users/krishnak/Library/Application Support/Objective-See/OverSight/OverSight.log" | grep "Video Device" | tail -n 1 | grep -q -w "active"
CAMERA_INIT_STATUS=$?

updateMicStatus $AUDIO_INIT_STATUS
updateCameraStatus $CAMERA_INIT_STATUS

tail -1f "/System/Volumes/Data/Users/krishnak/Library/Application Support/Objective-See/OverSight/OverSight.log" | awk '/Audio Device/ && /[^[:alpha:]]active/ { system("curl -X PUT $BASE_URL/mic?state=on") } /Audio Device/ && /inactive/ { system("curl -X PUT $BASE_URL/mic?state=off") }' &
tail -1f "/System/Volumes/Data/Users/krishnak/Library/Application Support/Objective-See/OverSight/OverSight.log" | awk '/Video Device/ && /[^[:alpha:]]active/ { system("curl -X PUT $BASE_URL/camera?state=on") } /Video Device/ && /inactive/ { system("curl -X PUT $BASE_URL/camera?state=off") }'
