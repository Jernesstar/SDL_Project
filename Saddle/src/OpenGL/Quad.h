#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"

#include "Saddle/Core/Assert.h"

namespace Saddle {

struct Quad {
    VertexArray* VertexArray;

    template<typename T, std::size_t TCount>
    Quad(const T (&vertices)[TCount], const BufferLayout& layout)
    {
        SADDLE_CORE_ASSERT(TCount == 4, "Quad requires 4 vertices");

        VertexBuffer vertex_buffer(vertices, layout);

        IndexBuffer index_buffer({
            0U, 1U, 2U,
            2U, 3U, 1U
        });

        VertexArray = new Saddle::VertexArray(vertex_buffer, index_buffer);
    }
};

}