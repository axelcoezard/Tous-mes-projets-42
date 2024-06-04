/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Thread.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:14:32 by acoezard          #+#    #+#             */
/*   Updated: 2024/04/22 08:39:50 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <thread>

struct GlobalContext;

class Thread
{
private:
	std::thread* m_Thread;

protected:
	GlobalContext* m_GlobalContext;

public:
	Thread(GlobalContext* serverData)
	{
		m_GlobalContext = serverData;
	}

	virtual ~Thread() {};

	void Initialize()
	{
		m_Thread = GetThread();
	}

	void Wait()
	{
		m_Thread->join();
	}

	virtual void Update() = 0;

	virtual std::thread* GetThread() = 0;
};
