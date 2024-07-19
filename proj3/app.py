from flask import Flask

app = Flask(__name__)
data=[]

@app.route("/distance/<distance>")
def getdistance(distance):
	global data
	data.append(distance)
	return 200,""

@app.route("/")
def showdistance():
	return data
