#include "ofApp.h"

vector<ofVec3f> vertices;
vector<ofVec3f> offsets;

int nPoints;		//The number of points
//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest;
	ofSetVerticalSync(true);
	ofSetGlobalAmbientColor(ofColor(0, 0, 0));
	ofSetSmoothLighting(true);

	ofSetFrameRate(60);

	nPoints = 1500;			//The number of points

	float Rad = 250;	//The to-be-formed sphere's (the 'dome' container) radius 

	//Fill the vertices array
	vertices.resize(nPoints);			//Set the array size
	for (int i = 0; i<nPoints; i++) {	//Scan all the points
										//Generate the center of the points
										//as a random point on the sphere

										//Take the random point from
										//cube [-1,1]x[-1,1]x[-1,1]	to form the sphere

		ofVec3f center(ofRandom(-1, 1),
			ofRandom(-1, 1),
			ofRandom(-1, 1));
		center.normalize(); //Normalize vector's length to 1

		center *= Rad;	//Now the center vector has
						//length Rad

		//Set the randomly selected vertices
		//as the center of the spheres
		vertices[i] = center;
		mesh.addVertex(vertices[i]);
		mesh.addColor(255);

		offsets.push_back(ofVec3f(ofRandom(0, 100000), ofRandom(0, 100000), ofRandom(0, 100000)));
	}

	//set the camera position at the center of the formed-sphere (the 'dome' container)
	cam.setDistance(Rad);

	/*
	//set spotlight with cut off value to highlight the depth
	spotlight.setSpotlight(30,10);
	//make the spotlight to follow the camera's point of focus
	spotlight.setParent(cam);
	*/

	pointLight.setDiffuseColor(ofColor(255, 252, 229));
	pointLight.setSpecularColor( ofColor(255.f, 255.f, 0.f));
	pointLight.setPointLight();
	pointLight.setPosition(ofGetWidth(), ofGetHeight(), Rad);
}

//--------------------------------------------------------------
void ofApp::update(){
	/*
	auto& verts = vertices;
	for (unsigned int i = 0; i < verts.size(); i++) {
		verts[i].x += ofSignedNoise(verts[i].x*ofRandom(-1., 2), verts[i].y / ofRandom(-1., 2), verts[i].z / ofRandom(-1., 2), ofGetElapsedTimef());
		verts[i].y += ofSignedNoise(verts[i].z*ofRandom(-1., 2), verts[i].x / ofRandom(-1., 2), verts[i].y / ofRandom(-1., 2), ofGetElapsedTimef());
		verts[i].z += ofSignedNoise(verts[i].y*ofRandom(-1., 2), verts[i].z / ofRandom(-1., 2), verts[i].x / ofRandom(-1., 2), ofGetElapsedTimef());
	}
	vertices = verts;
	*/

	int numVerts = mesh.getNumVertices();
	for (int i = 0; i<numVerts; ++i) {
		ofVec3f vert = mesh.getVertex(i);

		float time = ofGetElapsedTimef();
		float timeScale = 5.0;
		float displacementScale = 0.75;
		ofVec3f timeOffsets = offsets[i];

		// A typical design pattern for using Perlin noise uses a couple parameters:
		// ofSignedNoise(time*timeScale+timeOffset)*displacementScale
		//     ofSignedNoise(time) gives us noise values that change smoothly over time
		//     ofSignedNoise(time*timeScale) allows us to control the smoothness of our noise (smaller timeScale, smoother values)
		//     ofSignedNoise(time+timeOffset) allows us to use the same Perlin noise function to control multiple things and have them look as if they are moving independently
		//     ofSignedNoise(time)*displacementScale allows us to change the bounds of the noise from [-1, 1] to whatever we want 
		// Combine all of those parameters together, and you've got some nice control over your noise

		vert.x += (ofSignedNoise(time*timeScale + timeOffsets.x)) * displacementScale;
		vert.y += (ofSignedNoise(time*timeScale + timeOffsets.y)) * displacementScale;
		vert.z += (ofSignedNoise(time*timeScale + timeOffsets.z)) * displacementScale;
		mesh.setVertex(i, vert);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//Enable z-buffering
	glEnable(GL_DEPTH_TEST);

	ofBackground(17,41,71);
	ofEnableLighting();
	
	cam.begin();
	pointLight.enable();

	ofPushMatrix();	//Store the coordinate system

	//Calculate the rotation angle
	float time = ofGetElapsedTimef();	//Get time in seconds
	float angle = time * 20;			//Compute angle. We rotate at speed 10 degrees per second
	ofRotate(angle, 0, 1, 0);			//Rotate the coordinate system along y-axe
		
	mesh.drawVertices();
	
	//Draw lines between near points
	float connectionDistance = 30; //Threshold parameter of distance
	ofSetColor(255);	//Set color
	int numVerts = mesh.getNumVertices();
	for (int a = 0; a<numVerts; ++a) {
		ofVec3f verta = mesh.getVertex(a);
		for (int b = a + 1; b<numVerts; ++b) {
			ofVec3f vertb = mesh.getVertex(b);
			float distance = ofDist(verta.x, verta.y, verta.z, vertb.x, vertb.y, vertb.z);
			if (distance	< connectionDistance) {
				ofLine(ofVec3f(verta), ofVec3f(vertb));
			}
		}
	}
	
	ofPopMatrix();	//Restore the coordinate system

	pointLight.disable();
	cam.end();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
