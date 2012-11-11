#include <math.h>
#include <stdio.h>
#include <string.h>

#include "ppapi/cpp/completion_callback.h"
#include "ppapi/cpp/graphics_2d.h"
#include "ppapi/cpp/image_data.h"
#include "ppapi/cpp/input_event.h"
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/point.h"
#include "ppapi/cpp/var.h"

#include "includes/view.h"

namespace {

const uint32_t opaqueColorMask = 0xff000000;  // Opaque pixels.
const uint32_t whiteMask = 0xffbf0f;
const uint32_t blackMask = 0xff1c00;

const uint32_t whitePawnMask = 0xffffff;
const uint32_t blackPawnMask = 0x000000;

const uint32_t whitePawnHighlight = 0xaaaaaa;

// This is called by the browser when the 2D context has been flushed to the
// browser window.

void FlushCallback(void* data, int32_t result) {
	static_cast<checkers::View*>(data)->setFlushPending(false);
}

}  // namespace

namespace checkers {


View::View(pp::Instance* instance) : instance(instance){
	this->flushPending = false;	
	this->context = NULL;
	this->pixelBuffer = NULL;

	using namespace pp;
}

View::~View() {
  destroyContext();
  delete pixelBuffer;
}

pp::Size View::getSize() const {
	pp::Size size;
	if (context) {
		int width = context->size().width();
		int height = context->size().height();
		size.SetSize(width, height);
	}
	return size;
}

void View::drawBoard() {

	uint32_t* pixels = static_cast<uint32_t*>(pixelBuffer->data());
	
	if (pixels == NULL)
  	  return;

	const int32_t height = pixelBuffer->size().height();
	const int32_t width = pixelBuffer->size().width();

	for (int32_t py = 0; py < height; ++py) {
		for (int32_t px = 0; px < width; ++px) {
			for(int i=0; i<32; i++){			
				const int32_t pos = px + py * width;
				uint32_t color = opaqueColorMask;
				if (whiteField.at(i)->Contains(px, py)){
					color |= whiteMask;
					pixels[pos] = color;					
				}else if (blackField.at(i)->Contains(px, py)){
					color |= blackMask;
					pixels[pos] = color;					
				}
			}
		}
	}

  flushPixelBuffer();
}

void View::drawPawns(){
	uint32_t* pixels = static_cast<uint32_t*>(pixelBuffer->data());
	
	if (pixels == NULL)
  	  return;

	const int32_t height = pixelBuffer->size().height();
	const int32_t width = pixelBuffer->size().width();
	for (int32_t py = 0; py < height; ++py) {
		for (int32_t px = 0; px < width; ++px) {
			const int32_t pos = px + py * width;
			uint32_t color = opaqueColorMask;			
			for(unsigned i=0; i<whitePawns.size(); i++){			
				if (whitePawns.at(i)->Contains(px, py)){
					color |= whitePawnMask;
					pixels[pos] = color;					
				}
			}
			for(unsigned i=0; i<blackPawns.size(); i++){	
				if (blackPawns.at(i)->Contains(px, py)){
						color |= blackPawnMask;
						pixels[pos] = color;					
					}			
			}
		}
	}
  flushPixelBuffer();
}

void View::redrawRect(pp::Rect *rect, uint32_t color){
	uint32_t* pixels = static_cast<uint32_t*>(pixelBuffer->data());
	if (pixels == NULL)
  	  return;
	color |= opaqueColorMask;
	const int32_t width = pixelBuffer->size().width();
	for (int32_t py = rect->y(); py < rect->bottom(); ++py) {
		for (int32_t px = rect->x(); px < rect->right(); ++px) {
			const int32_t pos = px + py * width;
			pixels[pos] = color;					
		}
	}

  flushPixelBuffer();
}

void View::redraw(std::vector<pp::Rect *> rects, std::vector<int32_t> colors, bool queen){
	uint32_t* pixels = static_cast<uint32_t*>(pixelBuffer->data());
	if (pixels == NULL)
  	  return;
	int32_t color;
	const int32_t width = pixelBuffer->size().width();
	for(unsigned i=0; i<rects.size(); i++){
		pp::Rect *rect = rects.at(i);
		color = opaqueColorMask | colors.at(i);
		for (int32_t py = rect->y(); py < rect->bottom(); ++py) {
			for (int32_t px = rect->x(); px < rect->right(); ++px) {
				const int32_t pos = px + py * width;				
				if(queen && i==0 && py > rect->y()+10 )					
					pixels[pos] = 0xffff00;			
				else
					pixels[pos] = color;					
			}
		}
	}

  flushPixelBuffer();
}

void View::updateView(const pp::Rect& position, const pp::Rect& clip, pp::Instance* instance) {
	const int32_t width = pixelBuffer ? pixelBuffer->size().width() : 0;
	const int32_t height = pixelBuffer ? pixelBuffer->size().height() : 0;

	if (position.size().width() == width && position.size().height() == height)
		return;  // Size didn't change, no need to update anything.

	// Create a new device context with the new size.
	destroyContext();
	createContext(position.size(), instance);

	// Delete the old pixel buffer and create a new one.
	delete pixelBuffer;
	pixelBuffer = NULL;

	if (context != NULL) 
		pixelBuffer = new pp::ImageData(instance, PP_IMAGEDATAFORMAT_BGRA_PREMUL, context->size(), false);

}

void View::createContext(const pp::Size& size, pp::Instance* instance) {
	if (isContextValid())
    	return;
  	
	context = new pp::Graphics2D(instance, size, false);
	
	if (!instance->BindGraphics(*context)) 
		instance->PostMessage(pp::Var("ERROR: Couldn't bind the device context"));
	
}

void View::destroyContext() {
	if (!isContextValid())
		return;
	delete context;
	context = NULL;
}

void View::flushPixelBuffer() {
	if (!isContextValid())
		return;
  // Note that the pixel lock is held while the buffer is copied into the
  // device context and then flushed.
	context->PaintImageData(*pixelBuffer, pp::Point());
	if (flushPending)
		return;
	flushPending = true;
	context->Flush(pp::CompletionCallback(&FlushCallback, this));
}

bool View::isContextValid() const {
	return context != NULL;
}

}  // namespace checkers
