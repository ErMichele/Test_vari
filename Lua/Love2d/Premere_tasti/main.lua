local x = 0

function love.draw()
    love.graphics.print(x, 400, 300)
end

function love.keypressed(key)
    if key == "space" then
        x = x + 1
    end
end
