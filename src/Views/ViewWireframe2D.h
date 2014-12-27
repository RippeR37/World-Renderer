#ifndef VIEW_WIREFRAME_2D_H_INCLUDED
#define VIEW_WIREFRAME_2D_H_INCLUDED

#include "ExtendedView.h"

namespace View {

    class ViewWireframe2D : public ExtendedView<void> {
        public:
            ViewWireframe2D();
            ~ViewWireframe2D();

            void render();

        private:
            void setVertexData();
    };

}

#endif