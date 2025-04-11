local button = {
    x = 100,
    y = 100,
    width = 200,
    height = 50,
    text = "Cliccami",
    color = {0.3, 0.6, 0.9}
}

function love.load()
    love.graphics.setFont(love.graphics.newFont(20))
end

function love.draw()
    -- Disegna il bottone
    love.graphics.setColor(button.color)
    love.graphics.rectangle("fill", button.x, button.y, button.width, button.height)
    
    -- Disegna il testo
    love.graphics.setColor(1, 1, 1) -- Bianco
    local textX = button.x + button.width / 2 - love.graphics.getFont():getWidth(button.text) / 2
    local textY = button.y + button.height / 2 - love.graphics.getFont():getHeight(button.text) / 2
    love.graphics.print(button.text, textX, textY)
end

function love.mousepressed(x, y, buttonPressed)
    if buttonPressed == 1 and -- Controlla il click del mouse (bottone sinistro)
       x > button.x and x < button.x + button.width and
       y > button.y and y < button.y + button.height then
        print("Bottone cliccato!")
        button.color = {0.5, 0.8, 0.5} -- Cambia colore come feedback visivo
    end
end
