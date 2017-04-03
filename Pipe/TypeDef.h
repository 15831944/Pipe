#pragma once


namespace aht
{
	//	処理結果
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

	//	バー種別
	enum barKind{
		bid = 0,
		ask = 4,
		middle = 8
	};

	//	レート種別
	enum rateKind{
		open,
		high,
		low,
		close
	};
	
	//	時間枠
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

	//	適用価格
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

	//	ポジションサイド
	enum positionSide{
		flat,
		buy,
		sell
	};

	//	操作
	enum operation{
		buyMarket,
		sellMarket,
		buyLimit,
		sellLimit,
		buyStop,
		sellStop
	};

	//	ポジション種別
	enum positionKind{
		simulation,
		real
	};

	//	ポジション状態
	enum positionState{
		psOrdering,	//	注文中
		psOpen,		//	約定
		psClose,	//	決済済み
		psCancel	//	キャンセル
	};
	
	//	取引種別
	enum trade{
		longAndShort,
		longOnly,
		shortOnly,
		numOfTradeType
	};

	//	注文制限
	enum limitOrder{
		oneEntryOneExit,				//	売・買どちらか1回
		onlyOneEntryEachBuyAndSell,		//	売・買それぞれ1回
		unlimitedEntry					//	無制限
	};

	//	レートパス
	enum ratePath{
		simple,
		detailBar,
		openOnly
	};

	//	テストモード
	enum testMode{
		bidOnly,
		bidAsk
	};

	//	詳細バー位置
	enum detailBarLocation{
		prev,		//	詳細バーはメインバーの時間前
		inTime,		//	詳細バーはメインバーの時間中
		after		//	詳細バーはメインバーの時間後
	};

	//	最大ドローダウン種別
	enum maxDDKind{
		realizedLoss,						//	確定損
		realizedProfitLossToUnRealizedLoss,	//	確定損益－含み損
		numOfMaxDDKind						//	種類数
	};

	//	純資産種別
	enum equityKind{
		realizedProfitLoss,	//	確定損益
		unRealizedProfit,	//	含み益
		unRealizedLoss,		//	含み損
		numOfEquityKind		//	種類数
	};

	
	// for_each の引数を簡略化するテンプレート関数
	template <typename T_container, typename T_function>
	T_function for_each(T_container& rcontainer, T_function function) {
		return std::for_each(rcontainer.begin(), rcontainer.end(), function);
	}

	// 条件付 for_each 繰り返し処理を終了する場合はfunctionでtrueを返す
	template <typename T_container, typename T_function>
	void for_each_if(T_container& rcontainer, T_function function) {
		std::find_if(rcontainer.begin(), rcontainer.end(), function);
	}

	//	ポインターキャスト
	template<class T>
	T pointer_cast(LPVOID p){
		return static_cast<T>(p);
	}

	///////////////////////////////////////////////////////
	//
	//	STLタイプ定義

	typedef std::basic_ofstream<TCHAR> tofstream;
	typedef std::basic_ifstream<TCHAR, std::char_traits<TCHAR> > tifstream;
	typedef std::basic_string< TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tstring;
	typedef std::vector<double> vecDouble;
	typedef std::vector<int> vecInt;

	//	ポジションポインタタイプ定義
	//typedef std::unique_ptr<stPosition> positionPtr;
	
	//	ポジションコンテナタイプ定義(key=チケットNo, value=ポジション)
	//typedef std::unordered_map<int, positionPtr> positionContainer;

	//	ポジションリスト
	//typedef std::list<positionPtr> lstPosition;

	//	ポジションベクター
	//typedef std::vector<positionPtr> vecPosition;
};