#pragma once

class TradeData
{
public:
	TradeData();
	TradeData(const BYTE* value, size_t size){
		set(value, size);
	}

	virtual ~TradeData(void);

	const BYTE* get() const{
		return m_data;
	}

	void set(const BYTE* value, size_t size){
		m_size = min(size, sizeof(m_data)/sizeof(BYTE));

		memcpy(m_data, value, m_size);
	}

	size_t size() const{
		return m_size;
	}

private:

	BYTE m_data[32];

	size_t m_size;
};
