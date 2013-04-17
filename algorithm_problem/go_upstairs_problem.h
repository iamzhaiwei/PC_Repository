// go_upstairs_problem.h
//
// last-edit-by: <>
//
// Description:
// ��¥������
// ��20��¥�ݣ�����һ����1��2��4���������ж������Ϸ���
//////////////////////////////////////////////////////////////////////
#ifndef GO_UPSTAIRS_PROBLEM_H
#define GO_UPSTAIRS_PROBLEM_H 1

#include <vector>

namespace zhaiwei
{
// number_stairs: ¥�ݵ�̨������
// step: һ�������ߵ�̨�������Ǹ�����
// kinds_step: ���鳤��
int go_upstairs_problem(int number_stairs, int *step, int kinds_step)
{
	// opt[i]��ʾ�ߵ���i��̨�׵��߷���Ŀ
	std::vector<int> opt(number_stairs+1, 0);
	
	// �ߵ���0��̨�׵��߷���Ŀ��1����һ��Ҳ����
	opt[0] = 1;
	
	// ��̬�滮
	for (int i = 1; i <= number_stairs; ++i)
	{
		for (int j = 0; j < kinds_step; ++j)
		{
			if (i < step[j])
				break;
			opt[i] += opt[i-step[j]];
		}
	}
	return opt[number_stairs];
}

}

#endif // GO_UPSTAIRS_PROBLEM_H
//////////////////////////////////////////////////////////////////////
