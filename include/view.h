#include "ppapi/cpp/rect.h"
#include <vector>
namespace checkers{

class View {
	public:
		explicit View(pp::Instance* instance);
		~View();

		void setBlackField(std::vector<pp::Rect*> blackField) {
			this->blackField = blackField;
		}
		
		void setWhiteField(std::vector<pp::Rect*> whiteField) {
			this->whiteField = whiteField;
		}
	
		void setBlackPawns(std::vector<pp::Rect*> blackPawns) {
			this->blackPawns = blackPawns;
		}
		
		void setWhitePawns(std::vector<pp::Rect*> whitePawns) {
			this->whitePawns = whitePawns;
		}
		
		void setBlackQueens(std::vector<pp::Rect*> blackQueens) {
			this->blackQueens = blackQueens;
		}
		
		void setWhiteQueens(std::vector<pp::Rect*> whiteQueens) {
			this->whiteQueens = whiteQueens;
		}
		
		void setFlushPending(bool flushPending) {
			this->flushPending = flushPending;
			
		}

		pp::Size getSize() const;

		void drawBoard();
		void drawPawns();
		void redrawRect(pp::Rect *rect, uint32_t color);
		void redraw(std::vector<pp::Rect *> rects, std::vector<int32_t> colors, bool queen);
		
		void updateView(const pp::Rect& position, const pp::Rect& clip, pp::Instance* instance);

 private:
	pp::Instance* const instance;  // weak
	
	void createContext(const pp::Size& size, pp::Instance* instance);
	void destroyContext();

	// Push the pixels to the browser, then attempt to flush the 2D context.  If
	// there is a pending flush on the 2D context, then update the pixels only
	// and do not flush.
	void flushPixelBuffer();
	bool isContextValid() const;

	// Geometry for drawing
	std::vector<pp::Rect*> whiteField;
	std::vector<pp::Rect*> blackField;

	std::vector<pp::Rect*> whitePawns;
	std::vector<pp::Rect*> blackPawns;

	std::vector<pp::Rect*> whiteQueens;
	std::vector<pp::Rect*> blackQueens;

	// Drawing stuff
	bool flushPending;
	pp::Graphics2D* context;
	pp::ImageData* pixelBuffer;
};

} // namespace
