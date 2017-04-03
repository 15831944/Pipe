#pragma once


namespace aht
{
	//	��������
	enum result{
		rOk,
		rFail,
		rCancel,
		rNotExistBar,
		rNotExistPosition,
		rOutOfMemory,
		rInvalidOpenRate,
		rInvalidStopLoss,
		rInvalidLimit,
		rFailToOpenFile,
		rExistChart,
		rNotExistChart,
		rNotExistStrategy,
		rAlreadyRegistered,
		rFailToLoadStrategy,
		rFailToLoadIndicator,
		rFailToLoadCustomIndicator,
		rNotExistOrder,
		rOrderIsContracted,
		rNotExtistTestResult
	};

	//	�o�[���
	enum barKind{
		bid = 0,
		ask = 4,
		middle = 8
	};

	//	���[�g���
	enum rateKind{
		open,
		high,
		low,
		close
	};
	
	//	���Ԙg
	enum timeFrame{
		tick = 0,
		m1 = 1,
		m5 = 5,
		m10 = 10,
		m15 = 15,
		m30 = 30,
		h1 = 60,
		h4 = 240,
		d1 = 1440,
		w1 = 10080,
		mn1 = 43200
	};

	//	�K�p���i
	enum typicalPrice{
		O,
		H,
		L,
		C,
		HL,
		HLC,
		HLCC,
		HLCCC
	};

	//	�|�W�V�����T�C�h
	enum positionSide{
		flat,
		buy,
		sell
	};

	//	����
	enum operation{
		buyMarket,
		sellMarket,
		buyLimit,
		sellLimit,
		buyStop,
		sellStop
	};

	//	�|�W�V�������
	enum positionKind{
		simulation,
		real
	};

	//	�|�W�V�������
	enum positionState{
		psOrdering,	//	������
		psOpen,		//	���
		psClose,	//	���ύς�
		psCancel	//	�L�����Z��
	};
	
	//	������
	enum trade{
		longAndShort,
		longOnly,
		shortOnly,
		numOfTradeType
	};

	//	��������
	enum limitOrder{
		oneEntryOneExit,				//	���E���ǂ��炩1��
		onlyOneEntryEachBuyAndSell,		//	���E�����ꂼ��1��
		unlimitedEntry					//	������
	};

	//	���[�g�p�X
	enum ratePath{
		simple,
		detailBar,
		openOnly
	};

	//	�e�X�g���[�h
	enum testMode{
		bidOnly,
		bidAsk
	};

	//	�ڍ׃o�[�ʒu
	enum detailBarLocation{
		prev,		//	�ڍ׃o�[�̓��C���o�[�̎��ԑO
		inTime,		//	�ڍ׃o�[�̓��C���o�[�̎��Ԓ�
		after		//	�ڍ׃o�[�̓��C���o�[�̎��Ԍ�
	};

	//	�ő�h���[�_�E�����
	enum maxDDKind{
		realizedLoss,						//	�m�葹
		realizedProfitLossToUnRealizedLoss,	//	�m�葹�v�|�܂ݑ�
		numOfMaxDDKind						//	��ސ�
	};

	//	�����Y���
	enum equityKind{
		realizedProfitLoss,	//	�m�葹�v
		unRealizedProfit,	//	�܂݉v
		unRealizedLoss,		//	�܂ݑ�
		numOfEquityKind		//	��ސ�
	};

	
	// for_each �̈������ȗ�������e���v���[�g�֐�
	template <typename T_container, typename T_function>
	T_function for_each(T_container& rcontainer, T_function function) {
		return std::for_each(rcontainer.begin(), rcontainer.end(), function);
	}

	// �����t for_each �J��Ԃ��������I������ꍇ��function��true��Ԃ�
	template <typename T_container, typename T_function>
	void for_each_if(T_container& rcontainer, T_function function) {
		std::find_if(rcontainer.begin(), rcontainer.end(), function);
	}

	//	�|�C���^�[�L���X�g
	template<class T>
	T pointer_cast(LPVOID p){
		return static_cast<T>(p);
	}

	///////////////////////////////////////////////////////
	//
	//	STL�^�C�v��`

	typedef std::basic_ofstream<TCHAR> tofstream;
	typedef std::basic_ifstream<TCHAR, std::char_traits<TCHAR> > tifstream;
	typedef std::basic_string< TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tstring;
	typedef std::vector<double> vecDouble;
	typedef std::vector<int> vecInt;

	//	�|�W�V�����|�C���^�^�C�v��`
	//typedef std::unique_ptr<stPosition> positionPtr;
	
	//	�|�W�V�����R���e�i�^�C�v��`(key=�`�P�b�gNo, value=�|�W�V����)
	//typedef std::unordered_map<int, positionPtr> positionContainer;

	//	�|�W�V�������X�g
	//typedef std::list<positionPtr> lstPosition;

	//	�|�W�V�����x�N�^�[
	//typedef std::vector<positionPtr> vecPosition;
};