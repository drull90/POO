#include "caclibrary.h"

#include <vector>
#include <iostream>

using namespace std;

int main(int argc, const char **argv){

        checkCode c1(argc, argv, "articulo.cpp", "Orden: ./pedido_check articulo.cpp tarjeta.cpp usuario.cpp pedido.cpp pedido-articulo.cpp usuario-pedido.hpp -- -std=c++14 -I../P1");

        c1.setCorrectMessage("Verificación correcta de la clase Artículo.");
        c1.setIncorrectMessage("REVISA LOS ERRORES DE ARTÍCULO.");

        vector<string> functionNames = {"strlen", "strcat", "memset", "strcpy", "strcmp"};
        string headerName = "cstring";

        if(c1.findClass({"Articulo"})){

	        llvm::outs() << "* articulo.cpp:\n";

		c1.invocationsFromHeaders(functionNames, headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");

		c1.allPrivateVariableMember("Articulo", "Revisa el acceso a los atributos.");

		c1.notFriendMember("Articulo", "Revisa por qué es necesario incluir 'friend'.");

		c1.guardClauses("articulo.hpp", "Recuerda añadir las guardas de inclusión.");

                c1.check();

        }else{
                llvm::outs()<<"No se ha encontrado la clase 'Articulo'"<<"\n";
        }

        checkCode c2(argc, argv, "tarjeta.cpp", "");

        c2.setCorrectMessage("Verificación correcta de la clase Tarjeta.");
        c2.setIncorrectMessage("REVISA LOS ERRORES DE TARJETA.");

        if(c2.findClass({"Tarjeta"})){

		llvm::outs() << "* tarjeta.cpp:\n";

                c2.invocationsFromHeaders(functionNames, headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");
	
		c2.allPrivateVariableMember("Tarjeta", "Revisa el acceso a los atributos.");

		//Constructor copia y de asignación
		c2.deletedMethod({"Tarjeta", "operator="}, {{"const class Tarjeta &"}, {"const class Tarjeta &"}}, "Tarjeta", {"noconst", "noconst"}, "Revisa el enunciado respecto a la copia de objetos.");

		c2.guardClauses("tarjeta.hpp", "Recuerda añadir las guardas de inclusión.");

                vector<string> methodNames = {"tipo", "numero", "caducidad", "activa"};
                vector<vector<string> > parametersMethods = {{},{},{},{}};
                c2.inlineMethod(methodNames, parametersMethods, "Tarjeta", {"const", "const", "const", "const"}, "Sugerencia: incluir marca 'inline' a aquellos métodos con pocas instrucciones, como 'tipo()', 'numero()', 'caducidad()' o 'activa()'.");

                c2.check();

        }else{
                llvm::outs() << "No se ha encontrado la clase 'Tarjeta'"<<"\n";
        }

        checkCode c3(argc, argv,"usuario.cpp", "");

        c3.setCorrectMessage("Verificación correcta de la clase Usuario.");
        c3.setIncorrectMessage("REVISA LOS ERRORES DE USUARIO.");

        if(c3.findClass({"Usuario"})){

	        llvm::outs() << "* usuario.cpp:\n";

		c3.invocationsFromHeaders(functionNames, headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");                

		c3.allPrivateVariableMember("Usuario", "Revisa el acceso a los atributos.");
	
                //Constructor copia y de asignación
                c3.deletedMethod({"Usuario", "operator="}, {{"const class Usuario &"}, {"const class Usuario &"}}, "Usuario", {"noconst", "noconst"}, "Revisa el enunciado respecto a la copia de objetos.");	

		c3.numberOfConstructors("Usuario", 1, false, "Revisa el enunciado respecto a los constructores en esta clase.");
	
		c3.friendFunction({"operator<<"}, {{"?"}}, "Usuario", "Revisa si existen funciones que deben ser marcadas como amigas de la clase.");
		vector<string> methodNames = {"id", "nombre", "apellidos"};
		vector<vector<string> > parametersMethods = {{},{},{}};
		c3.inlineMethod(methodNames, parametersMethods, "Usuario", {"const", "const", "const"}, "Sugerencia: incluir marca 'inline' a aquellos métodos con pocas instrucciones, como 'id()', 'nombre()' o 'apellidos()'.");

		c3.guardClauses("usuario.hpp", "Recuerda añadir las guardas de inclusión.");	

                c3.check();

        }else{
                llvm::outs()<<"No se ha encontrado la clase 'Usuario'"<<"\n";
        }

	//Pedido-check
        checkCode c4(argc, argv,"pedido.cpp", "");

        c4.setCorrectMessage("Verificación correcta de la clase Pedido.");
        c4.setIncorrectMessage("REVISA LOS ERRORES DE PEDIDO.");

        if(c4.findClass({"Pedido"})){

	        llvm::outs() << "* pedido.cpp:\n";

		c4.invocationsFromHeaders(functionNames, headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");        
 
		c4.allPrivateVariableMember("Pedido", "Revisa el acceso a los atributos.");

                c4.numberOfConstructors("Pedido", 1, false, "Revisa el enunciado respecto a la construcción de objetos.");

                c4.defaultArgumentsInMethod({"Pedido"}, {{"?"}}, "Pedido", {"?"}, {1}, {{"Fecha()"}}, "Revisa el enunciado respecto a la construcción de objetos.");

                c4.listInitializerConstructor("Pedido", {"?"}, {"int", "const class Tarjeta *", "class Fecha", "double"}, "Revisa la lista de inicialización del constructor."); //Ponemos ? como lista de parámetros porque solo debe haber un constructor. La regla funcionará cualquiera sea el orden en el que se pongan los inicializadores en el constructor

		c4.function({"operator<<"}, {{"class std::basic_ostream<char> &", "const class Pedido &"}}, "Revisa el enunciado respecto al operador de extracción.");

                c4.memberVariable("Pedido", {"tarjeta_"}, {"const"}, {true}, "Revisa el enunciado respecto al atributo de la tarjeta de pago.");

                c4.guardClauses("pedido.hpp", "Recuerda añadir las guardas de inclusión");

                c4.check();
        }else{
                llvm::outs()<<"No se ha encontrado la clase 'Pedido'"<<"\n";
        }

        checkCode c5(argc, argv,"pedido-articulo.cpp", "");

        c5.setCorrectMessage("Verificación correcta de la clase Pedido_Articulo.");
        c5.setIncorrectMessage("REVISA LOS ERRORES DE PEDIDO_ARTICULO.");

        if(c5.findClass({"Pedido_Articulo", "LineaPedido"})){

	        llvm::outs() << "* pedido-articulo.cpp:\n";

                c5.numberOfConstructors("Pedido_Articulo", 0, false, "Revisa la necesidad de definir constructores.");

                c5.numberOfConstructors("LineaPedido", 1, false, "Revisa el enunciado respecto a los construcción de objetos.");

                vector<string> params = {"double", "unsigned int"};
                vector<vector<string> > methodsParams;
                methodsParams = {params};
                
		c5.defaultArgumentsInMethod({"LineaPedido"}, methodsParams, "LineaPedido", {"?"}, {1}, {{"1.*"}}, "Revisa el enunciado respecto a la construcción de objetos.");

                c5.explicitSpecifiedConstructor("LineaPedido", params, "Revisa el enunciado respecto a conversiones implícitas.");

                c5.function({"operator<<"}, {{"class std::basic_ostream<char> &", "const class LineaPedido &"}}, "Revisa el lugar de la declaración de los operadores.");

                //'pedir' sobrecargado puede hacerse mediante la busqueda de dos métodos con diferentes parametros.
                c5.method({"pedir","pedir"},{{"class Pedido &", "class Articulo &", "double", "unsigned int"}
                                    ,{"class Articulo &", "class Pedido &", "double", "unsigned int"}},
                                    "Pedido_Articulo", {"noconst","noconst"}, "Se sugiere la sobrecarga del método 'pedir'");

                c5.guardClauses("pedido-articulo.hpp", "Recuerda añadir las guardas de inclusión");

                c5.check();
        }else{
                llvm::outs()<<"No se ha encontrado la clase 'Pedido_Articulo'"<<"\n";
        }

        checkCode c6(argc, argv,"usuario-pedido.hpp", "");

        c6.setCorrectMessage("Verificación correcta de la clase Usuario_Pedido.");
        c6.setIncorrectMessage("REVISA LOS ERRORES DE USUARIO_PEDIDO.");

        if(c6.findClass({"Usuario_Pedido"})){

	        llvm::outs() << "* usuario-pedido.hpp:\n";

                c6.invocationsFromHeaders(functionNames, headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");

		c6.allPrivateVariableMember("Usuario_Pedido", "Revisa el acceso a los atributos.");

                c6.guardClauses("usuario-pedido.hpp", "Recuerda añadir las guardas de inclusión");

                c6.check();

        }else{
                llvm::outs()<<"No se ha encontrado la clase 'Usuario_Pedido'"<<"\n";
        }

        return 0;
}
