// DGM display to the exhibition track.
// creat piture data files using Digole picture converter 
// http://www.digole.com/tools/PicturetoC_Hex_converter.php
// picture converter http://www.digole.com/tools/PicturetoC_Hex_converter.php
// Code format HEX0x. Display position: From actualpicture to downscale.
// width: 240 Height: 320. 65K color, 2 bytes, for "EDIM2"
// Save the files as bin file. Rename the fileti img1.dat img2.dat img3.dat img10.dat
// Up to 10 image files is supported. Copy them to SD-card.
//
// Jørgen Bo Madsen - DGMF@jorgen-madsen.dk
// August 2025


#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial Display(8, 9); // RX, TX
File imageFile;

// Go back to what was working perfectly
#define DISPLAY_WIDTH 240   // Width that works perfectly
#define DISPLAY_HEIGHT 320  // Maximum height with 8-bit coordinates

// Image dimensions
#define IMAGE_WIDTH 240   
#define IMAGE_HEIGHT 320  

// Image settings - optimize for maximum speed
#define BYTES_PER_PIXEL 2  // RGB565 format
#define CHUNK_SIZE 120     // Much larger chunks for maximum speed (3x faster)

// Buffers - larger for faster drawing
uint8_t rgb565Buffer[CHUNK_SIZE * 2];

// Image management
uint8_t totalImages = 0;
uint8_t currentImageIndex = 0;
String imageFiles[10]; // Support up to 10 images

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Simple Image Display - 240x240"));
  
  // Initialize display
  InitializeDisplay();
  
  // Initialize SD card and find images
  while (!InitializeSDCard())
  {
    Serial.println(F("SD card failed! Retrying in 2 seconds..."));
    delay(2000);
  }
  
  // Find all image files
  FindImageFiles();
  
  if (totalImages == 0)
  {
    Serial.println(F("No image files found!"));
    while(1) delay(1000);
  }
  
  Serial.print(F("Found "));
  Serial.print(totalImages);
  Serial.println(F(" image files"));
}

void loop()
{
  // Display current image
  DisplayImage(currentImageIndex);
  
  // 3-second delay to view the image
  delay(3000);
  
  // Move to next image
  currentImageIndex++;
  if (currentImageIndex >= totalImages)
  {
    currentImageIndex = 0;
  }
}

void InitializeDisplay()
{
  Display.begin(9600);
  Display.print(F("DM")); // Graphics mode
  delay(100); // Reduced delay

  Display.print(F("CL"));
  delay(100); // Reduced delay
  
  // Try to increase baud rate for faster data transfer
  Display.println(F("SB115200"));
  Display.begin(115200);
  delay(200);
  
  Serial.println(F("Display initialized at high speed"));
}

bool InitializeSDCard()
{
  Serial.println(F("Initializing SD card..."));
  pinMode(10, OUTPUT);
  
  if (!SD.begin(4))
  {
    Serial.println(F("SD card initialization failed"));
    return false;
  }
  
  Serial.println(F("SD card initialized successfully"));
  return true;
}

void FindImageFiles()
{
  totalImages = 0;
  
  for (int i = 1; i <= 10; i++)
  {
    String filename = "IMG" + String(i) + ".DAT";
    
    if (SD.exists(filename))
    {
      imageFiles[totalImages] = filename;
      totalImages++;
      Serial.println("Found: " + filename);
    }
  }
}

void DisplayImage(uint8_t imageIndex)
{
  if (imageIndex >= totalImages) return;
  
  String filename = imageFiles[imageIndex];
  Serial.println("Displaying: " + filename);
  
  imageFile = SD.open(filename, FILE_READ);
  if (!imageFile)
  {
    Serial.println("Failed to open: " + filename);
    return;
  }
  
  // Clear screen first (removed delay for speed)
  // Display.print(F("CL"));
  
  // Display all lines as fast as possible
  for (uint16_t y = 0; y < DISPLAY_HEIGHT; y++)
  {
    DisplayImageLine(y);
  }
  
  imageFile.close();
  Serial.println("Image displayed successfully");
}

void DisplayImageLine(uint16_t y)
{
  // Show the full image with minimal compression
  uint16_t sourceY = ((unsigned long)y * IMAGE_HEIGHT) / DISPLAY_HEIGHT;
  
  // Make sure we don't exceed image bounds
  if (sourceY >= IMAGE_HEIGHT) {
    sourceY = IMAGE_HEIGHT - 1;
  }
  
  // Calculate file position for this line
  unsigned long lineStartPos = (unsigned long)sourceY * IMAGE_WIDTH * BYTES_PER_PIXEL;
  
  // Process the full line width in maximum-size chunks for speed
  for (uint16_t x = 0; x < DISPLAY_WIDTH; x += CHUNK_SIZE)
  {
    uint16_t pixelsToProcess = min(CHUNK_SIZE, DISPLAY_WIDTH - x);
    uint16_t bytesToRead = pixelsToProcess * BYTES_PER_PIXEL;
    
    // Calculate file position for this chunk
    unsigned long targetPos = lineStartPos + (unsigned long)x * BYTES_PER_PIXEL;
    imageFile.seek(targetPos);
    
    // Read RGB565 data from file
    if (imageFile.readBytes(rgb565Buffer, bytesToRead) == bytesToRead)
    {
      // Send to display immediately (no error checking delay)
      DrawBitmapChunk565(x, y, pixelsToProcess, 1, rgb565Buffer);
    }
  }
}

void DrawBitmapChunk565(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t* data)
{
  // Attention! https://www.digole.com/m/Imp_notice.htm
  // Use the EDIM2 format that works perfectly
  Display.print (F("EDIM2"));
  writePosition (x); 
  writePosition (y);
  writePosition (width);
  writePosition (height);
    // Send pixel data (2 bytes per pixel)
  Display.write(data, width * height * 2);
}


void writePosition (uint16_t position) { 
  if (position >= 255) {  // write two bytes when pixel value is more than 254
    Display.write(255);
    Display.write((uint8_t)(position - 255)); 
  } 
  else {  // one byte when pixel value is below 255
    Display.write((uint8_t)position);    
  }
}
