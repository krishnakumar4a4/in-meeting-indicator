package devicestate

import "log"

type DevState struct {
	Mic bool
	Camera bool
}

func NewDevState() *DevState {
	return &DevState{}
}

func (i *DevState) SetMic(enabled bool) {
	if i.Mic != enabled {
		log.Println("Toggling mic status to: ", enabled)
		i.Mic = enabled
	}
}

func (i *DevState) SetCamera(enabled bool) {
	if i.Camera != enabled {
		log.Println("Toggling camera status to: ", enabled)
		i.Camera = enabled
	}
}

func (i *DevState) IsMicEnabled() bool {
	return i.Mic
}

func (i *DevState) IsCameraEnabled() bool {
	return i.Camera
}