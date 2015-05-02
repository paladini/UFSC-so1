#ifndef QUEUE_H_
#define QUEUE_H_

namespace BOOOS {

	class Queue {
	public:
		Queue();

		virtual ~Queue();

		class Element {
		public:
			Element() { _prev = 0; _next = 0; }
			Element(int r) { _prev = 0; _next = 0; rank(r); }
			virtual ~Element() {}

			Element * prev() { return _prev; }
			Element * next() { return _next; }
			void prev(Element * p) { _prev = p; }
			void next(Element * p) { _next = p; }

			/*Funções do t4*/

			int rank() { return _rank; }

			void rank(int r) { _rank = r; }
			
			

			
			/*Fim das funções*/

		private:
			Element * _prev;
			Element * _next;

			//VARIAVEL T4
			int _rank;

		};

		Element * head() { return &_head; }

		int length() { return _length; }
                void removeItem(Element * item);
		void insert(Element * elem);
                void insereNaPosicao(Element * elem, int posicao);
                void insereComeco(Element * elem);
		void insert_ordered(Element * elem);
		Element* getItem(int pos);
		Element * remove();
	
		Element * imprime();

		//funcao T4
		void head(Element h){ _head = h; }

	private:
		Element _head;
		int _length;
	};

}

#endif //QUEUE_H_
