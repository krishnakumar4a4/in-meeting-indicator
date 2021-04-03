build:
	go build -o pa

update:
	BKP_DIR=pa.`date --iso-8601=hours`
	sudo mkdir -p /var/opt/bkps/pa.${BKP_DIR}
	sudo mv /var/opt/pa/* /var/opt/bkps/pa.${BKP_DIR}/
	sudo cp pa pa.service /var/opt/pa/
	sudo systemctl daemon-reload

