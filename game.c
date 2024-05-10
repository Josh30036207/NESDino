#include "LIB/neslib.h"
#include "LIB/nesdoug.h" 
#include "game.h"


#pragma bss-name(push, "ZEROPAGE")


	

void main (void) {
	
	ppu_off(); // screen off
	obs[0] = cacti;
	obs[1] = cacti2;
	obs[2] = birb;
	pal_bg(paletteBg); //	load the BG palette
	pal_spr(paletteSp);//load the sprite palette
	bank_spr(1);
	// set a starting point on the screen
	// vram_adr(NTADR_A(x,y));
	vram_adr(NTADR_A(3,3)); // screen is 32 x 30 tiles
	//clearScreen();
	
	set_vram_buffer(); // do at least once, sets a pointer to a buffer
	draw_bg();
	//set_scroll_y(0xff); //shift the bg down 1 pixel
	
	
	
	ppu_on_all(); //	turn on screen now in draw_bg();
	
	
	//while (loop){}

	while (loop){
		// infinite loop
		// game code can go here later.
		ppu_wait_nmi();
		pad1 = pad_poll(0); //read first controller input
		pad1_new = get_pad_new(0); // newly pressed button. do pad_poll first
		moveCloud();
		moveObs();
		checkCollision();
		drawSprites();
		abBtn();
		walk();
		displayScore();
		score++;

		//gameOver();
		while (pause){ //pause
			pad1 = pad_poll(0); 
			pad1_new = get_pad_new(0); 
			ssBtn();
		}
	}
	while (1){ //prevents crashes on "win"
		//hamburger
	}
}
	


void drawSprites(void){
	ppu_wait_nmi(); // wait till beginning of the frame
	// clear all sprites from sprite buffer
	oam_clear();
	bank_spr(1);//switch to player spritesheet

	
	{oam_meta_spr(dino.x, dino.y, dino.sprite);}//dino
	{oam_meta_spr(cloud.x, cloud.y, cloud.sprite);}//cloud
	for(i = 0; i < sizeof(obs) / (sizeof(char)*5); i++){oam_meta_spr(obs[i].x, obs[i].y, obs[i].sprite);}
	
	
}



void draw_bg(void){
	
	
	ppu_off(); // screen off
	set_vram_buffer(); // do at least once, sets a pointer to a buffer
	//copy the room to the collision map
	p_maps = All_Collision_Maps[which_bg];
	
	memcpy (c_map, p_maps, 240);
	set_data_pointer(p_maps);
	set_mt_pointer(mapTiles);
	
	
	for(y=0; ;y+=0x20){
		for(x=0; ;x+=0x20){
			address = get_ppu_addr(0, x, y);
			index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			flush_vram_update2();
			if (x == 0xe0) break;
		}
		if (y == 0xe0) break;
	}
	
	
	ppu_on_all(); // turn on screen
}

void abBtn(void){//jump
	if((pad1_new & PAD_A)||(pad1_new & PAD_B) ){
		if(jump == '0'){
			jump = '1';
			grnd = '0';
			dino.y-=2;
			dino.sprite = dinoStill;
		}
		
	}
	if((jump == '1')&&(fall == '0')&&(dino.y > 170)){
			dino.y-=2;
		}
	else if((dino.y <= 170)){
			dino.y+=2;
			fall = '1';
		}
	if((fall == '1')){
			dino.y+=2;
		}
	if((dino.y >= 211)){
			grnd = '1';
			jump = '0';
			fall = '0';
		}

	
}

void walk(void){
	if(jump!='1'){
	stepAlt = '0';
	if(steptimer < maxSTimer){
		stepAlt = '1';
			
	}
	else if(steptimer > (maxSTimer*2)){
		steptimer = 0;
	}
	steptimer++;
	
	switch(stepAlt){
	case '0':
		dino.sprite = dinoSp1;
	break;
	case '1':
		dino.sprite = dinoSp2;
	break;
	}

	

	}
}


void ssBtn(void){// Pause 
	if((pad1_new & PAD_SELECT)||(pad1_new & PAD_START) ){
		if (pause == 0){
			pause = 1;
		}else{pause = 0;}
		
	}
	
}


void gameOver(void){
	//Adds text to screen
	address = get_ppu_addr(0, 0x50, 0x50); 
	buffer_1_mt(address, 6);
	address = get_ppu_addr(0, 0x60, 0x50); 
	buffer_1_mt(address, 7);
	address = get_ppu_addr(0, 0x80, 0x50); 
	buffer_1_mt(address, 8);
	address = get_ppu_addr(0, 0x90, 0x50); 
	buffer_1_mt(address, 9);
	address = get_ppu_addr(0, 0x70, 0x60); 
	buffer_1_mt(address, 10);
	ppu_wait_nmi();

	//update high score
	if(score > hiScr){
		hiScr = score;
		mapTiles[(5*16)] = mapTiles[(5*13)];
		mapTiles[(5*16)+1] = mapTiles[(5*13)+1];
		mapTiles[(5*17)] = mapTiles[(5*14)];
		mapTiles[(5*17)+1] = mapTiles[(5*14)+1];
		mapTiles[(5*18)] = mapTiles[(5*15)];
		
	}
	

	


	pause = 1;
	while (pause){ //pause
			pad1 = pad_poll(0); 
			pad1_new = get_pad_new(0); 
			if((pad1_new & PAD_SELECT)||(pad1_new & PAD_START)||(pad1_new & PAD_A)||(pad1_new & PAD_B) ){
				
				pause = 0;

				reset();
			}
		}
}

void moveCloud(void){
	//moves the cloud
	cloud.x-=1;
	if((cloud.x==0)&&(filpFlop == '0')){
		
		cloud.sprite = clSp2;
	}
	else if((cloud.x==255)&&(filpFlop == '0')){cloud.sprite = clSp3;}
	else if((cloud.x==239)&&(filpFlop == '0')){cloud.sprite = clSp4;}
	else if(cloud.x==231){cloud.sprite = null;
		//cloudSprite = clSp;
		if(filpFlop == '0'){cloud.sprite = null; filpFlop = '1';}
		else{cloud.sprite = clSp; filpFlop = '0';}

		do{
			cloud.y = 4*rand8();
		}while(!((cloud.y <= 176) && (cloud.y >= 32)));
		}
	
}

void checkCollision(void){
	//checks the collisions between the dinosaur and the obstacles
	for(i = 0; i < sizeof(obs) / (sizeof(char)*5); i++){
		collision = check_collision(&dino, &obs[i]); 
		if (collision){gameOver();}
		
	}
	
}

void moveObs(void){

	for(i = 0; i < sizeof(obs) / (sizeof(char)*5); i++){
		if((obs[i].thrown == '0') && (trwTmr == 0)){
			rng = rand8();//sudo randomises the order that the obstacles come at the player
			rng = rng%2;
			if(rng == 1){
				obs[i].thrown = '1';
				trwTmr = 208;
				obs[i].x = 234;
				obs[i].sprite = obs[i].ogSpr;
			}
			
		}
		if(trwTmr > 0){
			trwTmr--;}
		
		if((obs[i].thrown == '1') ){
			obs[i].x-=2;
			
		}
		
		if((obs[i].x == 0) ){
			obs[i].thrown = '0';
			obs[i].sprite = null;
			
		}
	}
	

}

void reset(void){
	score = 0;
	for(i = 0; i < sizeof(obs) / (sizeof(char)*5); i++){
		obs[i].thrown = '0';
		obs[i].sprite = null;
		obs[i].x = 254;
	}
	dino.sprite=dinoSp1;
	dino.y = 211;

	mapTiles[(5*13)] = 64;
	mapTiles[(5*13)+1] = 64;
	mapTiles[(5*14)] = 64;
	mapTiles[(5*14)+1] = 64;
	mapTiles[(5*15)] = 64;
	
	

	for(i = 0; i < 10; i++){
        scrBrd[i] = 0;
    }
	draw_bg();
}

void displayScore(void){
	
	rtnDig(score);
	

	
	address = get_ppu_addr(0, 0xD0, 0x00); 
	mapTiles[(5*13)] = 64 + scrBrd[0];
	mapTiles[(5*13)+1] = 64 + scrBrd[1];
	buffer_1_mt(address, 13);

	address = get_ppu_addr(0, 0xE0, 0x00); 
	mapTiles[(5*14)] = 64 + scrBrd[2];
	mapTiles[(5*14)+1] = 64 + scrBrd[3];
	buffer_1_mt(address, 14);

	address = get_ppu_addr(0, 0xF0, 0x00); 
	mapTiles[(5*15)] = 64 + scrBrd[4];
	buffer_1_mt(address, 15);
	counter = 4;

	//high Score
	address = get_ppu_addr(0, 0x80, 0x00); 
	buffer_1_mt(address, 11);
	address = get_ppu_addr(0, 0x90, 0x00); 
	buffer_1_mt(address, 12);
	
	address = get_ppu_addr(0, 0xA0, 0x00); 
	buffer_1_mt(address, 16);
	address = get_ppu_addr(0, 0xB0, 0x00); 
	buffer_1_mt(address, 17);
	address = get_ppu_addr(0, 0xC0, 0x00); 
	buffer_1_mt(address, 18);

	

}

int rtnDig(value){

 	
    digit = value % 10;
	scrBrd[counter] = digit;
	
	counter--;
	if(value >= 10){
		
        rtnDig(value / 10);
	}
	
	return digit;
}

