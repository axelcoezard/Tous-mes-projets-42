//--------------------------------------------------//
//               LEVEL 8 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <cstring>
#include <cstdlib>

class N
{
	private:
		int		m_Value;
		char	m_Annotation[100];
	
	public:
	
		N(int n) : m_Value(n) {}

		int		operator+(N& n) {
			return m_Value + n.m_Value;
		}

		int		operator-(N& n) { 
			return m_Value - n.m_Value;
		}

		void	setAnnotation(char* annotation) {
			std::memcpy(m_Annotation, annotation, std::strlen(annotation));
		}
};

int main(int argc, char** argv)
{
	if (argc < 2) { /* WARNING: Subroutine does not return */
		return EXIT_FAILURE;
	}

	N* n1 = (N*) new N(5);
	N* n2 = (N*) new N(6);

	n1->setAnnotation(argv[1]); // N::setAnnotation(this,*(char **)(param_2 + 4));
	(*n1 + *n2); // (**(code **)*this_00)(this_00,this);

	return EXIT_SUCCESS;
}
