package main

import(
	"net/http"
	"fmt"
	"pa/devicestate"
	"log"
)

var devState *devicestate.DevState

func main() {
	mux := http.NewServeMux()
	mux.HandleFunc("/mic", handleMicState)
	mux.HandleFunc("/camera", handleCameraState)
	mux.HandleFunc("/*", handleUnknown)

	setup()
	if err := http.ListenAndServe(":3000", mux); err != nil {
		log.Println("listen error: ", err.Error())
	}
}

func setup() {
	devState = devicestate.NewDevState()
}

func handleMicState(rw http.ResponseWriter, r *http.Request) {
	if r.Method == http.MethodGet {
		rw.Write([]byte(fmt.Sprintf("%v", devState.IsMicEnabled())))
	} else if r.Method == http.MethodPut {
		qParams := r.URL.Query()
		devState.SetMic(qParams.Get("state") == "on")
		rw.WriteHeader(http.StatusOK)
	} else {
		rw.WriteHeader(http.StatusBadRequest)
	}
}

func handleCameraState(rw http.ResponseWriter, r *http.Request) {
	if r.Method == http.MethodGet {
		rw.Write([]byte(fmt.Sprintf("%v", devState.IsCameraEnabled())))
	} else if r.Method == http.MethodPut {
		qParams := r.URL.Query()
		devState.SetCamera(qParams.Get("state") == "on")
		rw.WriteHeader(http.StatusOK)
	} else {
		rw.WriteHeader(http.StatusBadRequest)
	}
}

func handleUnknown(rw http.ResponseWriter, r *http.Request) {
	log.Println("Unknown req received: ", r)
}