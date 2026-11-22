//place item with itemId into col and row of the spritesheet
function getItemInfo(itemId, col, row){
    //col = col*16;
    //row = row*16;
    arrayIndex = itemId-256;
    adjustedRow = row;
    iconValue = (adjustedRow << 5) | (col & 31)

    console.log(`ItemID: ${itemId}
        place into kItemIcon at index: ${arrayIndex}
        (row ${Math.floor(arrayIndex/8)} col ${(arrayIndex%8)}) - counting from 0
        value: ${iconValue}`)
}

//first value is item ID
//second and third value are col and row of where you want your texture to be located (16x16 grid)
getItemInfo(460,20,0) //again counting from 0