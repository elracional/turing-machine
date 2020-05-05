$(function() {  //Se incializan los elementos en el DOM 

    $('#cargar').click(function(){
        id = ID;
        if($('#cadena').val() == ""){
            $(this).popover('show');
            return false;
        }else{
            $(this).popover('hide');
            LoadString(id)
            Clear();
            return true;
        }
    });
/* 
   /////////////////////////////////////////////////////////////////////
   // Evalua segun el ragno selecionando,                             //
   // se ejecutara cada vez que se cada vez que se oprima el elemento //
   /////////////////////////////////////////////////////////////////////
*/
    $('#evaluar').click(

        function(){
            id = ID;
            time = 1000 - $("#rango").val();
            Tick = setInterval(function(){Evaluate(id)}, time);//Se ejecuta cuando se llama a la funcion Evaluate con la funcion setIterval asiganando el time del rango
        }

    );
});

/* 
   /////////////////////////////////////////////////////////////////////    
   // Se llena la Tabla con los row en blando, se dibuja la tabla     //
   /////////////////////////////////////////////////////////////////////
*/

// . 
function AddBlank(table){
    for(i = 0; i < 100; i++){
        AddRow(BLANK, "", "", table);
    }
    return true;
}
/*
    ////////////////////////////////////////////////////////////////////
    // Se carga la cadena dnetro de la tabla dentro de cada row,      //
    // se coloca una letra.                                           //
    ////////////////////////////////////////////////////////////////////
*/
function LoadString(table){
    var cadena = $('#cadena').val();
        ClearRows(table);
        AddRow(cadena.charAt(0), "active-row", "bg-info text-light", table);
        for(i = 1; i < cadena.length; i++){
            AddRow(cadena.charAt(i), "", "", table);
        }
        AddBlank(table);
        return true;
}
/*
    //////////////////////////////////////////////////////////////////////
    // Se evalua cada row que contiene cada caracter de la cadena,      //
    // paso a paso se evalua invocando la maquina selecionada.          //
    // La funcion recibira el caracter a evaluar y el id de la maquina, //
    // respentando la programacion de las reglas de cada una.           //
    //////////////////////////////////////////////////////////////////////
*/
function EvaluateStep(symbol, id){
    Machines[id].Count++;
    symbols = Machines[id][Machines[id].State]

    if(symbols[symbol] == undefined) return { Error : true, Acceptable : Machines[id].Functions.Acceptable(Machines[id].State), Message : `El símbolo <strong>'${symbol}'</strong> no tiene transición definida en el estado <strong>${Machines[id].State}</strong> de esta máquina. ${symbols.ERROR ? symbols.ERROR : ''}`};

    NextValues = symbols[symbol];
    Machines[id].State = NextValues[1];
    return { Error : false, Acceptable: Machines[id].Functions.Acceptable(Machines[id].State), Output : NextValues[0], Movement : NextValues[2] };
}

/*
    ////////////////////////////////////////////////////////////////
    // Se evalua toda la cadena cargada en la cinta (tabla),      //
    // recorrinedola y mandando a llamar la funcion EvaluateStep  //
    // la cual nos alluda a evaluar caracter por caracter         //       
    ////////////////////////////////////////////////////////////////
*/

function Evaluate(id){
        chain = $("#tabla" + id + " td");
        i = Machines[id].i;

        if(!Machines[id].Functions.Acceptable(Machines[id].State) && chain.length > i && Machines[id].Count < 10000){
            time = 1000 - $("#rango").val();
            result = EvaluateStep(chain[i].textContent.trim(), id);
            if(result.Error){
                Update();
                Stop();
                $('#modalTitle').html('¡Error!');
                $('#modalText').html(result.Message);
                $('#myModal').modal('show');
               
            }else{
                if (i >= chain.length - 2) AddBlank(id);
                chain[i].textContent = (result.Output);
                i += result.Movement;
                Machines[id].i += result.Movement;
                chain[i].setAttribute('id', 'new-row');
                ChangeActiveRow(id, time);
                Update();
            }

            
        }else{
            if(Machines[id].Functions.Acceptable(Machines[id].State)){
                Update();            
                Stop();
                $('#modalTitle').html('Cadena válida.');
                $('#modalText').html('La cadena ingresada es válida. Puede ver el resultado en la cinta.');
                $('#myModal').modal('show');
                
            }
    
            if(Machines[id].Count >= 10000){
                Update();
                Stop();
                $('#modalTitle').html('¡Error!');
                $('#modalText').html('La cadena ingresada ha generado muchas transiciones sin definir un resultado.');
                $('#myModal').modal('show');
            }
        }

        
}

/* 
   /////////////////////////////////////////////////////////////////////    
   // Funcion limpia el intervalo de tiempo o detiene la cinta        //
   /////////////////////////////////////////////////////////////////////
*/

function Stop(){
    clearInterval(Tick);
}

/* 
   /////////////////////////////////////////////////////////////////////    
   // Funciones de la maquinas,                                       //
   // Se generan matrices en donde se programas los estados validos   //
   // o bien se ponene las reglas del automata.                       //
   // si entra lo manda al siguinete estado valido y así hasta llegar //
   // a recorer toda la cinta y mandar a un estado final.             //  
   /////////////////////////////////////////////////////////////////////
*/

function SetMachine1(){
    Machines[1][0] = {
        '1' : ['X', 1, 1],
        '+' : ['+', 0, 1],
        '=' : ['=', 3, 1],
        "ERROR" : "La máquina dice: cadena vacía o formato incorrecto."
    };

    Machines[1][1] = {
        '1' : ['1', 1, 1],
        '+' : ['+', 4, 1],
        '=' : ['=', 1, 1],
        'ß' : ['1', 2, -1]
    };

    Machines[1][2] = {
        '1' : ['1', 2, -1],
        '+' : ['+', 2, -1],
        '=' : ['=', 2, -1],
        'X' : ['1', 0, 1]
    };

    Machines[1][3] = {
        '1' : ['1', 3, 1],
        'ß' : ['1', 3, 1]
    };

    Machines[1][4] = {
        '1' : ['1', 1, 1],
        "ERROR" : "La máquina dice: no existe símbolo unario después del símbolo operador."
    };

    Machines[1]['i'] = 0;
    Machines[1]['Count'] = 0;
    Machines[1]['State'] = 0;
    Machines[1]['Functions'] = {
        Acceptable(state) { return state == 3 }
    };
}


function SetMachine4(){

    Machines[4][0] = {
        'a' : ['ß', 1, 1],
        'b' : ['ß', 4, 1],
        'c' : ['ß', 7, 1],
        'ß' : ['ß', 10 , 1]
    }


    Machines[4][1] = {
        'a' : ['a', 1, 1],
        'b' : ['b', 1, 1],
        'c' : ['c', 1, 1],
        'ß' : ['ß', 2, -1] 
    }

    Machines[4][2] = {
        'a' : ['ß', 3, -1],
        'ß' : ['ß', 10, 1]
    }

    Machines[4][3] = {
        'ß' : ['ß', 0, 1],
        'a' : ['a', 3, -1],
        'b' : ['b', 3, -1],
        'c' : ['c', 3, -1],
    }

    Machines[4][4] = {
        'a' : ['a', 4, 1],
        'b' : ['b', 4, 1],
        'c' : ['c', 4, 1],
        'ß' : ['ß', 5, -1] 
    }

    Machines[4][5] = {
        'b' : ['ß', 6, -1],
        'ß' : ['ß', 10, 1]
    }

    Machines[4][6] = {
        'ß' : ['ß', 0, 1],
        'a' : ['a', 6, -1],
        'b' : ['b', 6, -1],
        'c' : ['c', 6, -1],
    }

    Machines[4][7] = {
        'a' : ['a', 7, 1],
        'b' : ['b', 7, 1],
        'c' : ['c', 7, 1],
        'ß' : ['ß', 8, -1] 
    }

    Machines[4][8] = {
        'c' : ['ß', 9, -1],
        'ß' : ['ß', 10, 1]
    }

    Machines[4][9] = {
        'ß' : ['ß', 0, 1],
        'a' : ['a', 9, -1],
        'b' : ['b', 9, -1],
        'c' : ['c', 9, -1],
    }

    Machines[4]['i'] = 0;
    Machines[4]['Count'] = 0;
    Machines[4]['State'] = 0;
    Machines[4]['Functions'] = {
        Acceptable(state) { return state == 10 }
    };
}

