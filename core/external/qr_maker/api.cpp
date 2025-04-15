#include <climits>
#include <sstream>
#include <string>

#include "api.h"
#include "src\qrcodegen.h"

namespace qr_maker {
        namespace detail {
            static std::string QrCodeToSVG(const qrcodegen::QrCode &qr, int border = 0) {
                if (border < 0)
                    throw std::domain_error("Border must be non-negative");
                if (border > INT_MAX / 2 || border * 2 > INT_MAX - qr.getSize())
                    throw std::overflow_error("Border too large");
                
                std::ostringstream result;
                result << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
                result << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
                result << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
                result << (qr.getSize() + border * 2) << " " << (qr.getSize() + border * 2) << "\" stroke=\"none\">\n";
                result << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
                result << "\t<path d=\"";
                for (int y = 0; y < qr.getSize(); y++) {
                    for (int x = 0; x < qr.getSize(); x++) {
                        if (qr.getModule(x, y)) {
                            if (x != 0 || y != 0)
                                result << " ";
                            result << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
                        }
                    }
                }
                result << "\" fill=\"#000000\"/>\n";
                result << "</svg>\n";
                return result.str();
            }
        } //namespace detail

        std::string GenerateSvgQrCode(const std::string& value) {
			const auto qr = qrcodegen::QrCode::encodeText(value.c_str(), qrcodegen::QrCode::Ecc::MEDIUM);
			return detail::QrCodeToSVG(qr);
		}

} //namespace qr_maker

