const unsigned char dinoStill[]={
	  0,  0,0x00,0,
	  8,  0,0x01,0,
	  0,  8,0x10,0,
	  8,  8,0x11,0,
	128
};

const unsigned char dinoSp1[]={
	  0,  0,0x00,0,
	  8,  0,0x01,0,
	  0,  8,0x02,0,
	  8,  8,0x03,0,
	128
};

const unsigned char dinoSp2[]={
	  0,  0,0x00,0,
	  8,  0,0x01,0,
	  0,  8,0x12,0,
	  8,  8,0x13,0,
	128
};

const unsigned char cSp1[]={
	  0,  0,0x04,0,
	  0,  8,0x14,0,
	128
};

const unsigned char cSp2[]={
	  0,  0,0x05,0,
	  8,  0,0x06,0,
	  0,  8,0x15,0,
	  8,  8,0x16,0,
	128
};

const unsigned char bSp[]={
	  0,  0,0x08,0,
	  8,  0,0x09,0,
	  0,  8,0x18,0,
	  8,  8,0x19,0,
	128
};

const unsigned char clSp[]={
	  
	  8,  0,0x0B,0,
	  16,  0,0x0C,0,
	  24,  0,0x0D,0,

	  0,  8,0x1A,0,
	  8,  8,0x1B,0,
	  16,  8,0x1C,0,
	  24,  8,0x1D,0,
	128
};

const unsigned char clSp2[]={
	  
	  8,  0,0x0B,0,
	  16,  0,0x0C,0,
	  24,  0,0x0D,0,

	  8,  8,0x1B,0,
	  16,  8,0x1C,0,
	  24,  8,0x1D,0,
	128
};

const unsigned char clSp3[]={
	  
	  16,  0,0x0C,0,
	  24,  0,0x0D,0,

	
	  16,  8,0x1C,0,
	  24,  8,0x1D,0,
	128
};

const unsigned char clSp4[]={
	  24,  0,0x0D,0,
	  24,  8,0x1D,0,
	128
};


const unsigned char null[]={
	128
};

//Colours

const  char paletteBg[]={ //palette for the background
0x30, 0x06, 0x10, 0x0f,
0x0f,0x10,0x06,0x27,
0,0,0,0,
0,0,0,0
}; 
const  char paletteSp[]={//palette for the sprites
0x30, 0x06, 0x10, 0x0f,
0x0f,0x10,0x06,0x27,
0,0,0,0,
0,0,0,0
}; 

char mapTiles[]={ //per row TTL, TR, BL, BR, Colour 
	5, 5, 5, 5,  0,//Empty Space
	0, 0, 5, 5,  0,//Tile 1
	1, 1, 5, 5,  0,//Tile 2
	2, 2, 5, 5,  0,//Tile 3
	3, 3, 5, 5,  0,//Tile 4
	4, 4, 5, 5,  0,//Tile 5
	96, 97, 5, 5,  0,//GA
	98, 99, 5, 5,  0,//ME
	100, 101, 5, 5,  0,//OV
	102, 103, 5, 5,  0,//GA
	104, 105, 120, 121,  0,//retryBtn
	5, 48, 5, 5,  0,// H
	49, 50, 5, 5,  0,//I: 
	64, 64, 5, 5, 0,// Spaces 1 & 2
	64, 64, 5, 5, 0,// Spaces 3 & 4
	64, 5, 5, 5, 0,// Spaces 5 & 6
	64, 64, 5, 5, 0,// Spaces 1 & 2 - high Score
	64, 64, 5, 5, 0,// Spaces 3 & 4 - high Score
	64, 5, 5, 5, 0,// Spaces 5 - high Score

};